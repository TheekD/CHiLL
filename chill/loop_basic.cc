/*
 * loop_basic.cc
 *
 *  Created on: Nov 12, 2012
 *      Author: anand
 */

#include "loop.hh"
#include "chill_error.hh"
#include <omega.h>
#include "omegatools.hh"
#include <string.h>

using namespace omega;

void Loop::permute(const std::vector<int> &pi) {
	std::set<int> active;
	for (int i = 0; i < stmt.size(); i++)
		active.insert(i);

	permute(active, pi);
}

void Loop::original() {
	std::set<int> active;
	for (int i = 0; i < stmt.size(); i++)
		active.insert(i);
	setLexicalOrder(0, active);
}
void Loop::permute(int stmt_num, int level, const std::vector<int> &pi) {
	// check for sanity of parameters
	int starting_order;
	if (stmt_num < 0 || stmt_num >= stmt.size())
		throw std::invalid_argument(
				"invalid statement number " + to_string(stmt_num));
	std::set<int> active;
	if (level < 0 || level > stmt[stmt_num].loop_level.size())
		throw std::invalid_argument("invalid loop level " + to_string(level));
	else if (level == 0) {
		for (int i = 0; i < stmt.size(); i++)
			active.insert(i);
		level = 1;
		starting_order = 0;
	} else {
		std::vector<int> lex = getLexicalOrder(stmt_num);
		active = getStatements(lex, 2 * level - 2);
		starting_order = lex[2 * level - 2];
		lex[2 * level - 2]++;
		shiftLexicalOrder(lex, 2 * level - 2, active.size() - 1);
	}
	std::vector<int> pi_inverse(pi.size(), 0);
	for (int i = 0; i < pi.size(); i++) {
		if (pi[i] >= level + pi.size() || pi[i] < level
				|| pi_inverse[pi[i] - level] != 0)
			throw std::invalid_argument("invalid permuation");
		pi_inverse[pi[i] - level] = level + i;
	}
	for (std::set<int>::iterator i = active.begin(); i != active.end(); i++)
		if (level + pi.size() - 1 > stmt[*i].loop_level.size())
			throw std::invalid_argument(
					"invalid permutation for statement " + to_string(*i));

	// invalidate saved codegen computation
	delete last_compute_cgr_;
	last_compute_cgr_ = NULL;
	delete last_compute_cg_;
	last_compute_cg_ = NULL;

	// Update transformation relations
	for (std::set<int>::iterator i = active.begin(); i != active.end(); i++) {
		int n = stmt[*i].xform.n_out();
		Relation mapping(n, n);
		F_And *f_root = mapping.add_and();
		for (int j = 1; j <= 2 * level - 2; j++) {
			EQ_Handle h = f_root->add_EQ();
			h.update_coef(mapping.output_var(j), 1);
			h.update_coef(mapping.input_var(j), -1);
		}
		for (int j = level; j <= level + pi.size() - 1; j++) {
			EQ_Handle h = f_root->add_EQ();
			h.update_coef(mapping.output_var(2 * j), 1);
			h.update_coef(mapping.input_var(2 * pi[j - level]), -1);
		}
		for (int j = level; j <= level + pi.size() - 1; j++) {
			EQ_Handle h = f_root->add_EQ();
			h.update_coef(mapping.output_var(2 * j - 1), 1);
			h.update_coef(mapping.input_var(2 * j - 1), -1);
		}
		for (int j = 2 * (level + pi.size() - 1) + 1; j <= n; j++) {
			EQ_Handle h = f_root->add_EQ();
			h.update_coef(mapping.output_var(j), 1);
			h.update_coef(mapping.input_var(j), -1);
		}
		stmt[*i].xform = Composition(mapping, stmt[*i].xform);
		stmt[*i].xform.simplify();
	}

	// get the permuation for dependence vectors
	std::vector<int> t;
	for (int i = 0; i < pi.size(); i++)
		if (stmt[stmt_num].loop_level[pi[i] - 1].type == LoopLevelOriginal)
			t.push_back(stmt[stmt_num].loop_level[pi[i] - 1].payload);
	int max_dep_dim = -1;
	int min_dep_dim = dep.num_dim();
	for (int i = 0; i < t.size(); i++) {
		if (t[i] > max_dep_dim)
			max_dep_dim = t[i];
		if (t[i] < min_dep_dim)
			min_dep_dim = t[i];
	}
	if (min_dep_dim > max_dep_dim)
		return;
	if (max_dep_dim - min_dep_dim + 1 != t.size())
		throw loop_error("cannot update the dependence graph after permuation");
	std::vector<int> dep_pi(dep.num_dim());
	for (int i = 0; i < min_dep_dim; i++)
		dep_pi[i] = i;
	for (int i = min_dep_dim; i <= max_dep_dim; i++)
		dep_pi[i] = t[i - min_dep_dim];
	for (int i = max_dep_dim + 1; i < dep.num_dim(); i++)
		dep_pi[i] = i;

	dep.permute(dep_pi, active);

	// update the dependence graph
	DependenceGraph g(dep.num_dim());
	for (int i = 0; i < dep.vertex.size(); i++)
		g.insert();
	for (int i = 0; i < dep.vertex.size(); i++)
		for (DependenceGraph::EdgeList::iterator j =
				dep.vertex[i].second.begin(); j != dep.vertex[i].second.end();
				j++) {
			if ((active.find(i) != active.end()
					&& active.find(j->first) != active.end())) {
				std::vector<DependenceVector> dv = j->second;
				for (int k = 0; k < dv.size(); k++) {
					switch (dv[k].type) {
					case DEP_W2R:
					case DEP_R2W:
					case DEP_W2W:
					case DEP_R2R: {
						std::vector<coef_t> lbounds(dep.num_dim());
						std::vector<coef_t> ubounds(dep.num_dim());
						for (int d = 0; d < dep.num_dim(); d++) {
							lbounds[d] = dv[k].lbounds[dep_pi[d]];
							ubounds[d] = dv[k].ubounds[dep_pi[d]];
						}
						dv[k].lbounds = lbounds;
						dv[k].ubounds = ubounds;
						break;
					}
					case DEP_CONTROL: {
						break;
					}
					default:
						throw loop_error("unknown dependence type");
					}
				}
				g.connect(i, j->first, dv);
			} else if (active.find(i) == active.end()
					&& active.find(j->first) == active.end()) {
				std::vector<DependenceVector> dv = j->second;
				g.connect(i, j->first, dv);
			} else {
				std::vector<DependenceVector> dv = j->second;
				for (int k = 0; k < dv.size(); k++)
					switch (dv[k].type) {
					case DEP_W2R:
					case DEP_R2W:
					case DEP_W2W:
					case DEP_R2R: {
						for (int d = 0; d < dep.num_dim(); d++)
							if (dep_pi[d] != d) {
								dv[k].lbounds[d] = -posInfinity;
								dv[k].ubounds[d] = posInfinity;
							}
						break;
					}
					case DEP_CONTROL:
						break;
					default:
						throw loop_error("unknown dependence type");
					}
				g.connect(i, j->first, dv);
			}
		}
	dep = g;

	// update loop level information
	for (std::set<int>::iterator i = active.begin(); i != active.end(); i++) {
		int cur_dep_dim = min_dep_dim;
		std::vector<LoopLevel> new_loop_level(stmt[*i].loop_level.size());
		for (int j = 1; j <= stmt[*i].loop_level.size(); j++)
			if (j >= level && j < level + pi.size()) {
				switch (stmt[*i].loop_level[pi_inverse[j - level] - 1].type) {
				case LoopLevelOriginal:
					new_loop_level[j - 1].type = LoopLevelOriginal;
					new_loop_level[j - 1].payload = cur_dep_dim++;
					new_loop_level[j - 1].parallel_level =
							stmt[*i].loop_level[pi_inverse[j - level] - 1].parallel_level;
					break;
				case LoopLevelTile: {
					new_loop_level[j - 1].type = LoopLevelTile;
					int ref_level = stmt[*i].loop_level[pi_inverse[j - level]
							- 1].payload;
					if (ref_level >= level && ref_level < level + pi.size())
						new_loop_level[j - 1].payload = pi_inverse[ref_level
								- level];
					else
						new_loop_level[j - 1].payload = ref_level;
					new_loop_level[j - 1].parallel_level = stmt[*i].loop_level[j
							- 1].parallel_level;
					break;
				}
				default:
					throw loop_error(
							"unknown loop level information for statement "
									+ to_string(*i));
				}
			} else {
				switch (stmt[*i].loop_level[j - 1].type) {
				case LoopLevelOriginal:
					new_loop_level[j - 1].type = LoopLevelOriginal;
					new_loop_level[j - 1].payload =
							stmt[*i].loop_level[j - 1].payload;
					new_loop_level[j - 1].parallel_level = stmt[*i].loop_level[j
							- 1].parallel_level;
					break;
				case LoopLevelTile: {
					new_loop_level[j - 1].type = LoopLevelTile;
					int ref_level = stmt[*i].loop_level[j - 1].payload;
					if (ref_level >= level && ref_level < level + pi.size())
						new_loop_level[j - 1].payload = pi_inverse[ref_level
								- level];
					else
						new_loop_level[j - 1].payload = ref_level;
					new_loop_level[j - 1].parallel_level = stmt[*i].loop_level[j
							- 1].parallel_level;
					break;
				}
				default:
					throw loop_error(
							"unknown loop level information for statement "
									+ to_string(*i));
				}
			}
		stmt[*i].loop_level = new_loop_level;
	}

	setLexicalOrder(2 * level - 2, active, starting_order);
}
void Loop::permute(const std::set<int> &active, const std::vector<int> &pi) {
	if (active.size() == 0 || pi.size() == 0)
		return;

	// check for sanity of parameters
	int level = pi[0];
	for (int i = 1; i < pi.size(); i++)
		if (pi[i] < level)
			level = pi[i];
	if (level < 1)
		throw std::invalid_argument("invalid permuation");
	std::vector<int> reverse_pi(pi.size(), 0);
	for (int i = 0; i < pi.size(); i++)
		if (pi[i] >= level + pi.size())
			throw std::invalid_argument("invalid permutation");
		else
			reverse_pi[pi[i] - level] = i + level;
	for (int i = 0; i < reverse_pi.size(); i++)
		if (reverse_pi[i] == 0)
			throw std::invalid_argument("invalid permuation");
	int ref_stmt_num;
	std::vector<int> lex;
	for (std::set<int>::iterator i = active.begin(); i != active.end(); i++) {
		if (*i < 0 || *i >= stmt.size())
			throw std::invalid_argument("invalid statement " + to_string(*i));
		if (i == active.begin()) {
			ref_stmt_num = *i;
			lex = getLexicalOrder(*i);
		} else {
			if (level + pi.size() - 1 > stmt[*i].loop_level.size())
				throw std::invalid_argument("invalid permuation");
			std::vector<int> lex2 = getLexicalOrder(*i);
			for (int j = 0; j < 2 * level - 3; j += 2)
				if (lex[j] != lex2[j])
					throw std::invalid_argument(
							"statements to permute must be in the same subloop");
			for (int j = 0; j < pi.size(); j++)
				if (!(stmt[*i].loop_level[level + j - 1].type
						== stmt[ref_stmt_num].loop_level[level + j - 1].type
						&& stmt[*i].loop_level[level + j - 1].payload
								== stmt[ref_stmt_num].loop_level[level + j - 1].payload))
					throw std::invalid_argument(
							"permuted loops must have the same loop level types");
		}
	}
	// invalidate saved codegen computation
	delete last_compute_cgr_;
	last_compute_cgr_ = NULL;
	delete last_compute_cg_;
	last_compute_cg_ = NULL;

	// Update transformation relations
	for (std::set<int>::iterator i = active.begin(); i != active.end(); i++) {
		int n = stmt[*i].xform.n_out();
		Relation mapping(n, n);
		F_And *f_root = mapping.add_and();
		for (int j = 1; j <= n; j += 2) {
			EQ_Handle h = f_root->add_EQ();
			h.update_coef(mapping.output_var(j), 1);
			h.update_coef(mapping.input_var(j), -1);
		}
		for (int j = 0; j < pi.size(); j++) {
			EQ_Handle h = f_root->add_EQ();
			h.update_coef(mapping.output_var(2 * (level + j)), 1);
			h.update_coef(mapping.input_var(2 * pi[j]), -1);
		}
		for (int j = 1; j < level; j++) {
			EQ_Handle h = f_root->add_EQ();
			h.update_coef(mapping.output_var(2 * j), 1);
			h.update_coef(mapping.input_var(2 * j), -1);
		}
		for (int j = level + pi.size(); j <= stmt[*i].loop_level.size(); j++) {
			EQ_Handle h = f_root->add_EQ();
			h.update_coef(mapping.output_var(2 * j), 1);
			h.update_coef(mapping.input_var(2 * j), -1);
		}

		stmt[*i].xform = Composition(mapping, stmt[*i].xform);
		stmt[*i].xform.simplify();
	}

	// get the permuation for dependence vectors
	std::vector<int> t;
	for (int i = 0; i < pi.size(); i++)
		if (stmt[ref_stmt_num].loop_level[pi[i] - 1].type == LoopLevelOriginal)
			t.push_back(stmt[ref_stmt_num].loop_level[pi[i] - 1].payload);
	int max_dep_dim = -1;
	int min_dep_dim = num_dep_dim;
	for (int i = 0; i < t.size(); i++) {
		if (t[i] > max_dep_dim)
			max_dep_dim = t[i];
		if (t[i] < min_dep_dim)
			min_dep_dim = t[i];
	}
	if (min_dep_dim > max_dep_dim)
		return;
	if (max_dep_dim - min_dep_dim + 1 != t.size())
		throw loop_error("cannot update the dependence graph after permuation");
	std::vector<int> dep_pi(num_dep_dim);
	for (int i = 0; i < min_dep_dim; i++)
		dep_pi[i] = i;
	for (int i = min_dep_dim; i <= max_dep_dim; i++)
		dep_pi[i] = t[i - min_dep_dim];
	for (int i = max_dep_dim + 1; i < num_dep_dim; i++)
		dep_pi[i] = i;

	dep.permute(dep_pi, active);

	// update the dependence graph
	DependenceGraph g(dep.num_dim());
	for (int i = 0; i < dep.vertex.size(); i++)
		g.insert();
	for (int i = 0; i < dep.vertex.size(); i++)
		for (DependenceGraph::EdgeList::iterator j =
				dep.vertex[i].second.begin(); j != dep.vertex[i].second.end();
				j++) {         //
			if ((active.find(i) != active.end()
					&& active.find(j->first) != active.end())) {
				std::vector<DependenceVector> dv = j->second;
				for (int k = 0; k < dv.size(); k++) {
					switch (dv[k].type) {
					case DEP_W2R:
					case DEP_R2W:
					case DEP_W2W:
					case DEP_R2R: {
						std::vector<coef_t> lbounds(num_dep_dim);
						std::vector<coef_t> ubounds(num_dep_dim);
						for (int d = 0; d < num_dep_dim; d++) {
							lbounds[d] = dv[k].lbounds[dep_pi[d]];
							ubounds[d] = dv[k].ubounds[dep_pi[d]];
						}
						dv[k].lbounds = lbounds;
						dv[k].ubounds = ubounds;
						break;
					}
					case DEP_CONTROL: {
						break;
					}
					default:
						throw loop_error("unknown dependence type");
					}
				}
				g.connect(i, j->first, dv);
			} else if (active.find(i) == active.end()
					&& active.find(j->first) == active.end()) {
				std::vector<DependenceVector> dv = j->second;
				g.connect(i, j->first, dv);
			} else {
				std::vector<DependenceVector> dv = j->second;
				for (int k = 0; k < dv.size(); k++)
					switch (dv[k].type) {
					case DEP_W2R:
					case DEP_R2W:
					case DEP_W2W:
					case DEP_R2R: {
						for (int d = 0; d < num_dep_dim; d++)
							if (dep_pi[d] != d) {
								dv[k].lbounds[d] = -posInfinity;
								dv[k].ubounds[d] = posInfinity;
							}
						break;
					}
					case DEP_CONTROL:
						break;
					default:
						throw loop_error("unknown dependence type");
					}
				g.connect(i, j->first, dv);
			}
		}
	dep = g;

	// update loop level information
	for (std::set<int>::iterator i = active.begin(); i != active.end(); i++) {
		int cur_dep_dim = min_dep_dim;
		std::vector<LoopLevel> new_loop_level(stmt[*i].loop_level.size());
		for (int j = 1; j <= stmt[*i].loop_level.size(); j++)
			if (j >= level && j < level + pi.size()) {
				switch (stmt[*i].loop_level[reverse_pi[j - level] - 1].type) {
				case LoopLevelOriginal:
					new_loop_level[j - 1].type = LoopLevelOriginal;
					new_loop_level[j - 1].payload = cur_dep_dim++;
					new_loop_level[j - 1].parallel_level =
							stmt[*i].loop_level[reverse_pi[j - level] - 1].parallel_level;
					break;
				case LoopLevelTile: {
					new_loop_level[j - 1].type = LoopLevelTile;
					int ref_level = stmt[*i].loop_level[reverse_pi[j - level]
							- 1].payload;
					if (ref_level >= level && ref_level < level + pi.size())
						new_loop_level[j - 1].payload = reverse_pi[ref_level
								- level];
					else
						new_loop_level[j - 1].payload = ref_level;
					new_loop_level[j - 1].parallel_level =
							stmt[*i].loop_level[reverse_pi[j - level] - 1].parallel_level;
					break;
				}
				default:
					throw loop_error(
							"unknown loop level information for statement "
									+ to_string(*i));
				}
			} else {
				switch (stmt[*i].loop_level[j - 1].type) {
				case LoopLevelOriginal:
					new_loop_level[j - 1].type = LoopLevelOriginal;
					new_loop_level[j - 1].payload =
							stmt[*i].loop_level[j - 1].payload;
					new_loop_level[j - 1].parallel_level = stmt[*i].loop_level[j
							- 1].parallel_level;
					break;
				case LoopLevelTile: {
					new_loop_level[j - 1].type = LoopLevelTile;
					int ref_level = stmt[*i].loop_level[j - 1].payload;
					if (ref_level >= level && ref_level < level + pi.size())
						new_loop_level[j - 1].payload = reverse_pi[ref_level
								- level];
					else
						new_loop_level[j - 1].payload = ref_level;
					new_loop_level[j - 1].parallel_level = stmt[*i].loop_level[j
							- 1].parallel_level;
					break;
				}
				default:
					throw loop_error(
							"unknown loop level information for statement "
									+ to_string(*i));
				}
			}
		stmt[*i].loop_level = new_loop_level;
	}

	setLexicalOrder(2 * level - 2, active);
}

std::set<int> Loop::split(int stmt_num, int level, const Relation &cond) {
	// check for sanity of parameters
	if (stmt_num < 0 || stmt_num >= stmt.size())
		throw std::invalid_argument("invalid statement " + to_string(stmt_num));
	if (level <= 0 || level > stmt[stmt_num].loop_level.size())
		throw std::invalid_argument("invalid loop level " + to_string(level));

	std::set<int> result;
	int dim = 2 * level - 1;
	std::vector<int> lex = getLexicalOrder(stmt_num);
	std::set<int> same_loop = getStatements(lex, dim - 1);

	Relation cond2 = copy(cond);
	cond2.simplify();
	cond2 = EQs_to_GEQs(cond2);
	Conjunct *c = cond2.single_conjunct();
	int cur_lex = lex[dim - 1];

	for (GEQ_Iterator gi(c->GEQs()); gi; gi++) {
		int max_level = (*gi).max_tuple_pos();
		Relation single_cond(max_level);
		single_cond.and_with_GEQ(*gi);

		// TODO: should decide where to place newly created statements with
		// complementary split condition from dependence graph.
		bool place_after;
		if (max_level == 0)
			place_after = true;
		else if ((*gi).get_coef(cond2.set_var(max_level)) < 0)
			place_after = true;
		else
			place_after = false;

		bool temp_place_after;      // = place_after;
		bool assigned = false;
		int part1_to_part2;
		int part2_to_part1;
		// original statements with split condition,
		// new statements with complement of split condition
		int old_num_stmt = stmt.size();
		std::map<int, int> what_stmt_num;
		apply_xform(same_loop);
		for (std::set<int>::iterator i = same_loop.begin();
				i != same_loop.end(); i++) {
			int n = stmt[*i].IS.n_set();
			Relation part1, part2;
			if (max_level > n) {
				part1 = copy(stmt[*i].IS);
				part2 = Relation::False(0);
			} else {
				part1 = Intersection(copy(stmt[*i].IS),
						Extend_Set(copy(single_cond), n - max_level));
				part2 = Intersection(copy(stmt[*i].IS),
						Extend_Set(Complement(copy(single_cond)),
								n - max_level));
			}

			//split dependence check

			if (max_level > level) {

				DNF_Iterator di1(stmt[*i].IS.query_DNF());
				DNF_Iterator di2(part1.query_DNF());
				for (; di1 && di2; di1++, di2++) {
					//printf("In next conjunct,\n");
					EQ_Iterator ei1 = (*di1)->EQs();
					EQ_Iterator ei2 = (*di2)->EQs();
					for (; ei1 && ei2; ei1++, ei2++) {
						//printf(" In next equality constraint,\n");
						Constr_Vars_Iter cvi1(*ei1);
						Constr_Vars_Iter cvi2(*ei2);
						int dimension = (*cvi1).var->get_position();
						int same = 0;
						bool identical = false;
						if (identical = !strcmp((*cvi1).var->char_name(),
								(*cvi2).var->char_name())) {

							for (; cvi1 && cvi2; cvi1++, cvi2++) {

								if (((*cvi1).coef != (*cvi2).coef
										|| (*ei1).get_const()
												!= (*ei2).get_const())
										|| (strcmp((*cvi1).var->char_name(),
												(*cvi2).var->char_name()))) {

									same++;
								}
							}
						}
						if ((same != 0) || !identical) {

							dimension = dimension - 1;

							while (stmt[*i].loop_level[dimension].type
									== LoopLevelTile)
								dimension =
										stmt[*i].loop_level[dimension].payload;

							dimension = stmt[*i].loop_level[dimension].payload;

							for (int i = 0; i < stmt.size(); i++) {
								std::vector < std::pair<int, DependenceVector>
										> D;
								for (DependenceGraph::EdgeList::iterator j =
										dep.vertex[i].second.begin();
										j != dep.vertex[i].second.end(); j++) {
									for (int k = 0; k < j->second.size(); k++) {
										DependenceVector dv = j->second[k];
										if (dv.type != DEP_CONTROL)
											if (dv.hasNegative(dimension)
													&& !dv.quasi)
												throw loop_error(
														"loop error: Split is illegal, dependence violation!");

									}
								}
							}

						}

						GEQ_Iterator gi1 = (*di1)->GEQs();
						GEQ_Iterator gi2 = (*di2)->GEQs();

						for (; gi1 && gi2; gi++, gi2++) {

							Constr_Vars_Iter cvi1(*gi1);
							Constr_Vars_Iter cvi2(*gi2);
							int dimension = (*cvi1).var->get_position();
							int same = 0;
							bool identical = false;
							if (identical = !strcmp((*cvi1).var->char_name(),
									(*cvi2).var->char_name())) {

								for (; cvi1 && cvi2; cvi1++, cvi2++) {

									if (((*cvi1).coef != (*cvi2).coef
											|| (*gi1).get_const()
													!= (*gi2).get_const())
											|| (strcmp((*cvi1).var->char_name(),
													(*cvi2).var->char_name()))) {

										same++;
									}
								}
							}
							if ((same != 0) || !identical) {
								dimension = dimension - 1;

								while (stmt[*i].loop_level[dimension].type
										== LoopLevelTile)
									stmt[*i].loop_level[dimension].payload;

								dimension =
										stmt[*i].loop_level[dimension].payload;

								for (int i = 0; i < stmt.size(); i++) {
									std::vector
											< std::pair<int, DependenceVector>
											> D;
									for (DependenceGraph::EdgeList::iterator j =
											dep.vertex[i].second.begin();
											j != dep.vertex[i].second.end();
											j++) {
										for (int k = 0; k < j->second.size();
												k++) {
											DependenceVector dv = j->second[k];
											if (dv.type != DEP_CONTROL)
												if (dv.hasNegative(dimension)
														&& !dv.quasi)

													throw loop_error(
															"loop error: Split is illegal, dependence violation!");

										}
									}
								}

							}

						}

					}

				}

				DNF_Iterator di3(stmt[*i].IS.query_DNF());
				DNF_Iterator di4(part2.query_DNF());        //
				for (; di3 && di4; di3++, di4++) {
					EQ_Iterator ei1 = (*di3)->EQs();
					EQ_Iterator ei2 = (*di4)->EQs();
					for (; ei1 && ei2; ei1++, ei2++) {
						Constr_Vars_Iter cvi1(*ei1);
						Constr_Vars_Iter cvi2(*ei2);
						int dimension = (*cvi1).var->get_position();
						int same = 0;
						bool identical = false;
						if (identical = !strcmp((*cvi1).var->char_name(),
								(*cvi2).var->char_name())) {

							for (; cvi1 && cvi2; cvi1++, cvi2++) {

								if (((*cvi1).coef != (*cvi2).coef
										|| (*ei1).get_const()
												!= (*ei2).get_const())
										|| (strcmp((*cvi1).var->char_name(),
												(*cvi2).var->char_name()))) {

									same++;
								}
							}
						}
						if ((same != 0) || !identical) {
							dimension = dimension - 1;

							while (stmt[*i].loop_level[dimension].type
									== LoopLevelTile)
								stmt[*i].loop_level[dimension].payload;

							dimension = stmt[*i].loop_level[dimension].payload;

							for (int i = 0; i < stmt.size(); i++) {
								std::vector < std::pair<int, DependenceVector>
										> D;
								for (DependenceGraph::EdgeList::iterator j =
										dep.vertex[i].second.begin();
										j != dep.vertex[i].second.end(); j++) {
									for (int k = 0; k < j->second.size(); k++) {
										DependenceVector dv = j->second[k];
										if (dv.type != DEP_CONTROL)
											if (dv.hasNegative(dimension)
													&& !dv.quasi)

												throw loop_error(
														"loop error: Split is illegal, dependence violation!");

									}
								}
							}

						}

					}
					GEQ_Iterator gi1 = (*di3)->GEQs();
					GEQ_Iterator gi2 = (*di4)->GEQs();

					for (; gi1 && gi2; gi++, gi2++) {
						Constr_Vars_Iter cvi1(*gi1);
						Constr_Vars_Iter cvi2(*gi2);
						int dimension = (*cvi1).var->get_position();
						int same = 0;
						bool identical = false;
						if (identical = !strcmp((*cvi1).var->char_name(),
								(*cvi2).var->char_name())) {

							for (; cvi1 && cvi2; cvi1++, cvi2++) {

								if (((*cvi1).coef != (*cvi2).coef
										|| (*gi1).get_const()
												!= (*gi2).get_const())
										|| (strcmp((*cvi1).var->char_name(),
												(*cvi2).var->char_name()))) {

									same++;
								}
							}
						}
						if ((same != 0) || !identical) {
							dimension = dimension - 1;

							while (stmt[*i].loop_level[dimension].type        //
							== LoopLevelTile)
								stmt[*i].loop_level[dimension].payload;

							dimension = stmt[*i].loop_level[dimension].payload;

							for (int i = 0; i < stmt.size(); i++) {
								std::vector < std::pair<int, DependenceVector>
										> D;
								for (DependenceGraph::EdgeList::iterator j =
										dep.vertex[i].second.begin();
										j != dep.vertex[i].second.end(); j++) {
									for (int k = 0; k < j->second.size(); k++) {
										DependenceVector dv = j->second[k];
										if (dv.type != DEP_CONTROL)
											if (dv.hasNegative(dimension)
													&& !dv.quasi)

												throw loop_error(
														"loop error: Split is illegal, dependence violation!");

									}
								}
							}

						}

					}

				}

			}

			stmt[*i].IS = part1;

			if (Intersection(copy(part2),
					Extend_Set(copy(this->known), n - this->known.n_set())).is_upper_bound_satisfiable()) {
				Statement new_stmt;
				new_stmt.code = stmt[*i].code->clone();
				new_stmt.IS = part2;
				new_stmt.xform = copy(stmt[*i].xform);
				new_stmt.ir_stmt_node = NULL;
				new_stmt.loop_level = stmt[*i].loop_level;

				stmt_nesting_level_.push_back(stmt_nesting_level_[*i]);

				/*std::pair<std::vector<DependenceVector>,
				 std::vector<DependenceVector> > dv =
				 test_data_dependences(ir, stmt[*i].code, part1,
				 stmt[*i].code, part2, freevar, index,
				 stmt_nesting_level_[*i],
				 stmt_nesting_level_[stmt.size() - 1]);




				 for (int k = 0; k < dv.first.size(); k++)
				 part1_to_part2++;
				 if (part1_to_part2 > 0 && part2_to_part1 > 0)
				 throw loop_error(
				 "loop error: Aborting, split resulted in impossible dependence cycle!");

				 for (int k = 0; k < dv.second.size(); k++)
				 part2_to_part1++;



				 if (part1_to_part2 > 0 && part2_to_part1 > 0)
				 throw loop_error(
				 "loop error: Aborting, split resulted in impossible dependence cycle!");



				 if (part2_to_part1 > 0){
				 temp_place_after = false;
				 assigned = true;

				 }else if (part1_to_part2 > 0){
				 temp_place_after = true;

				 assigned = true;
				 }

				 */

				if (place_after)
					assign_const(new_stmt.xform, dim - 1, cur_lex + 1);
				else
					assign_const(new_stmt.xform, dim - 1, cur_lex - 1);

				stmt.push_back(new_stmt);
				dep.insert();
				what_stmt_num[*i] = stmt.size() - 1;
				if (*i == stmt_num)
					result.insert(stmt.size() - 1);
			}

		}
		// make adjacent lexical number available for new statements
		if (place_after) {
			lex[dim - 1] = cur_lex + 1;
			shiftLexicalOrder(lex, dim - 1, 1);
		} else {
			lex[dim - 1] = cur_lex - 1;
			shiftLexicalOrder(lex, dim - 1, -1);
		}
		// update dependence graph
		int dep_dim = get_dep_dim_of(stmt_num, level);
		for (int i = 0; i < old_num_stmt; i++) {
			std::vector < std::pair<int, std::vector<DependenceVector> > > D;

			for (DependenceGraph::EdgeList::iterator j =
					dep.vertex[i].second.begin();
					j != dep.vertex[i].second.end(); j++) {
				if (same_loop.find(i) != same_loop.end()) {
					if (same_loop.find(j->first) != same_loop.end()) {
						if (what_stmt_num.find(i) != what_stmt_num.end()
								&& what_stmt_num.find(j->first)
										!= what_stmt_num.end())
							dep.connect(what_stmt_num[i],
									what_stmt_num[j->first], j->second);
						if (place_after
								&& what_stmt_num.find(j->first)
										!= what_stmt_num.end()) {
							std::vector<DependenceVector> dvs;
							for (int k = 0; k < j->second.size(); k++) {
								DependenceVector dv = j->second[k];
								if (dv.is_data_dependence() && dep_dim != -1) {
									dv.lbounds[dep_dim] = -posInfinity;
									dv.ubounds[dep_dim] = posInfinity;
								}
								dvs.push_back(dv);
							}
							if (dvs.size() > 0)
								D.push_back(
										std::make_pair(what_stmt_num[j->first],
												dvs));
						} else if (!place_after
								&& what_stmt_num.find(i)
										!= what_stmt_num.end()) {
							std::vector<DependenceVector> dvs;
							for (int k = 0; k < j->second.size(); k++) {
								DependenceVector dv = j->second[k];
								if (dv.is_data_dependence() && dep_dim != -1) {
									dv.lbounds[dep_dim] = -posInfinity;
									dv.ubounds[dep_dim] = posInfinity;
								}
								dvs.push_back(dv);
							}
							if (dvs.size() > 0)
								dep.connect(what_stmt_num[i], j->first, dvs);

						}
					} else {
						if (what_stmt_num.find(i) != what_stmt_num.end())
							dep.connect(what_stmt_num[i], j->first, j->second);
					}
				} else if (same_loop.find(j->first) != same_loop.end()) {
					if (what_stmt_num.find(j->first) != what_stmt_num.end())
						D.push_back(
								std::make_pair(what_stmt_num[j->first],
										j->second));
				}
			}

			for (int j = 0; j < D.size(); j++)
				dep.connect(i, D[j].first, D[j].second);
		}

	}

	return result;
}

void Loop::skew(const std::set<int> &stmt_nums, int level,
		const std::vector<int> &skew_amount) {
	if (stmt_nums.size() == 0)
		return;

	// check for sanity of parameters
	int ref_stmt_num = *(stmt_nums.begin());
	for (std::set<int>::const_iterator i = stmt_nums.begin();
			i != stmt_nums.end(); i++) {
		if (*i < 0 || *i >= stmt.size())
			throw std::invalid_argument(
					"invalid statement number " + to_string(*i));
		if (level < 1 || level > stmt[*i].loop_level.size())
			throw std::invalid_argument(
					"invalid loop level " + to_string(level));
		for (int j = stmt[*i].loop_level.size(); j < skew_amount.size(); j++)
			if (skew_amount[j] != 0)
				throw std::invalid_argument("invalid skewing formula");
	}

	// invalidate saved codegen computation
	delete last_compute_cgr_;
	last_compute_cgr_ = NULL;
	delete last_compute_cg_;
	last_compute_cg_ = NULL;

	// set trasformation relations
	for (std::set<int>::const_iterator i = stmt_nums.begin();
			i != stmt_nums.end(); i++) {
		int n = stmt[*i].xform.n_out();
		Relation r(n, n);
		F_And *f_root = r.add_and();
		for (int j = 1; j <= n; j++)
			if (j != 2 * level) {
				EQ_Handle h = f_root->add_EQ();
				h.update_coef(r.input_var(j), 1);
				h.update_coef(r.output_var(j), -1);
			}
		EQ_Handle h = f_root->add_EQ();
		h.update_coef(r.output_var(2 * level), -1);
		for (int j = 0; j < skew_amount.size(); j++)
			if (skew_amount[j] != 0)
				h.update_coef(r.input_var(2 * (j + 1)), skew_amount[j]);

		stmt[*i].xform = Composition(r, stmt[*i].xform);
		stmt[*i].xform.simplify();
	}

	// update dependence graph
	if (stmt[ref_stmt_num].loop_level[level - 1].type == LoopLevelOriginal) {
		int dep_dim = stmt[ref_stmt_num].loop_level[level - 1].payload;
		for (std::set<int>::const_iterator i = stmt_nums.begin();
				i != stmt_nums.end(); i++)
			for (DependenceGraph::EdgeList::iterator j =
					dep.vertex[*i].second.begin();
					j != dep.vertex[*i].second.end(); j++)
				if (stmt_nums.find(j->first) != stmt_nums.end()) {
					// dependence between skewed statements
					std::vector<DependenceVector> dvs = j->second;
					for (int k = 0; k < dvs.size(); k++) {
						DependenceVector &dv = dvs[k];
						if (dv.is_data_dependence()) {
							coef_t lb = 0;
							coef_t ub = 0;
							for (int kk = 0; kk < skew_amount.size(); kk++) {
								int cur_dep_dim = get_dep_dim_of(*i, kk + 1);
								if (skew_amount[kk] > 0) {
									if (lb != -posInfinity
											&& stmt[*i].loop_level[kk].type
													== LoopLevelOriginal&& dv.lbounds[cur_dep_dim]
													!= -posInfinity)
										lb += skew_amount[kk]
												* dv.lbounds[cur_dep_dim];
									else {
										if (cur_dep_dim != -1
												&& !(dv.lbounds[cur_dep_dim]
														== 0
														&& dv.ubounds[cur_dep_dim]
																== 0))
											lb = -posInfinity;
									}
									if (ub != posInfinity
											&& stmt[*i].loop_level[kk].type
													== LoopLevelOriginal&& dv.ubounds[cur_dep_dim]
													!= posInfinity)
										ub += skew_amount[kk]
												* dv.ubounds[cur_dep_dim];
									else {
										if (cur_dep_dim != -1
												&& !(dv.lbounds[cur_dep_dim]
														== 0
														&& dv.ubounds[cur_dep_dim]
																== 0))
											ub = posInfinity;
									}
								} else if (skew_amount[kk] < 0) {
									if (lb != -posInfinity
											&& stmt[*i].loop_level[kk].type
													== LoopLevelOriginal&& dv.ubounds[cur_dep_dim]
													!= posInfinity)
										lb += skew_amount[kk]
												* dv.ubounds[cur_dep_dim];
									else {
										if (cur_dep_dim != -1
												&& !(dv.lbounds[cur_dep_dim]
														== 0
														&& dv.ubounds[cur_dep_dim]
																== 0))
											lb = -posInfinity;
									}
									if (ub != posInfinity
											&& stmt[*i].loop_level[kk].type
													== LoopLevelOriginal&& dv.lbounds[cur_dep_dim]
													!= -posInfinity)
										ub += skew_amount[kk]
												* dv.lbounds[cur_dep_dim];
									else {
										if (cur_dep_dim != -1
												&& !(dv.lbounds[cur_dep_dim]
														== 0
														&& dv.ubounds[cur_dep_dim]
																== 0))
											ub = posInfinity;
									}
								}
							}
							dv.lbounds[dep_dim] = lb;
							dv.ubounds[dep_dim] = ub;
							if ((dv.isCarried(dep_dim)
									&& dv.hasPositive(dep_dim)) && dv.quasi)
								dv.quasi = false;

							if ((dv.isCarried(dep_dim)
									&& dv.hasNegative(dep_dim)) && !dv.quasi)
								throw loop_error(
										"loop error: Skewing is illegal, dependence violation!");
							dv.lbounds[dep_dim] = lb;
							dv.ubounds[dep_dim] = ub;
							if ((dv.isCarried(dep_dim)
									&& dv.hasPositive(dep_dim)) && dv.quasi)
								dv.quasi = false;

							if ((dv.isCarried(dep_dim)
									&& dv.hasNegative(dep_dim)) && !dv.quasi)
								throw loop_error(
										"loop error: Skewing is illegal, dependence violation!");
						}
					}
					j->second = dvs;
				} else {
					// dependence from skewed statement to unskewed statement becomes jumbled,
					// put distance value at skewed dimension to unknown
					std::vector<DependenceVector> dvs = j->second;
					for (int k = 0; k < dvs.size(); k++) {
						DependenceVector &dv = dvs[k];
						if (dv.is_data_dependence()) {
							dv.lbounds[dep_dim] = -posInfinity;
							dv.ubounds[dep_dim] = posInfinity;
						}
					}
					j->second = dvs;
				}
		for (int i = 0; i < dep.vertex.size(); i++)
			if (stmt_nums.find(i) == stmt_nums.end())
				for (DependenceGraph::EdgeList::iterator j =
						dep.vertex[i].second.begin();
						j != dep.vertex[i].second.end(); j++)
					if (stmt_nums.find(j->first) != stmt_nums.end()) {
						// dependence from unskewed statement to skewed statement becomes jumbled,
						// put distance value at skewed dimension to unknown
						std::vector<DependenceVector> dvs = j->second;
						for (int k = 0; k < dvs.size(); k++) {
							DependenceVector &dv = dvs[k];
							if (dv.is_data_dependence()) {
								dv.lbounds[dep_dim] = -posInfinity;
								dv.ubounds[dep_dim] = posInfinity;
							}
						}
						j->second = dvs;
					}
	}
}

void Loop::shift(const std::set<int> &stmt_nums, int level, int shift_amount) {
	if (stmt_nums.size() == 0)
		return;

	// check for sanity of parameters
	int ref_stmt_num = *(stmt_nums.begin());
	for (std::set<int>::const_iterator i = stmt_nums.begin();
			i != stmt_nums.end(); i++) {
		if (*i < 0 || *i >= stmt.size())
			throw std::invalid_argument(
					"invalid statement number " + to_string(*i));
		if (level < 1 || level > stmt[*i].loop_level.size())
			throw std::invalid_argument(
					"invalid loop level " + to_string(level));
	}

	// do nothing
	if (shift_amount == 0)
		return;

	// invalidate saved codegen computation
	delete last_compute_cgr_;
	last_compute_cgr_ = NULL;
	delete last_compute_cg_;
	last_compute_cg_ = NULL;

	// set trasformation relations
	for (std::set<int>::const_iterator i = stmt_nums.begin();
			i != stmt_nums.end(); i++) {
		int n = stmt[*i].xform.n_out();

		Relation r(n, n);
		F_And *f_root = r.add_and();
		for (int j = 1; j <= n; j++) {
			EQ_Handle h = f_root->add_EQ();
			h.update_coef(r.input_var(j), 1);
			h.update_coef(r.output_var(j), -1);
			if (j == 2 * level)
				h.update_const(shift_amount);
		}

		stmt[*i].xform = Composition(r, stmt[*i].xform);
		stmt[*i].xform.simplify();
	}

	// update dependence graph
	if (stmt[ref_stmt_num].loop_level[level - 1].type == LoopLevelOriginal) {
		int dep_dim = stmt[ref_stmt_num].loop_level[level - 1].payload;
		for (std::set<int>::const_iterator i = stmt_nums.begin();
				i != stmt_nums.end(); i++)
			for (DependenceGraph::EdgeList::iterator j =
					dep.vertex[*i].second.begin();
					j != dep.vertex[*i].second.end(); j++)
				if (stmt_nums.find(j->first) == stmt_nums.end()) {
					// dependence from shifted statement to unshifted statement
					std::vector<DependenceVector> dvs = j->second;
					for (int k = 0; k < dvs.size(); k++) {
						DependenceVector &dv = dvs[k];
						if (dv.is_data_dependence()) {
							if (dv.lbounds[dep_dim] != -posInfinity)
								dv.lbounds[dep_dim] -= shift_amount;
							if (dv.ubounds[dep_dim] != posInfinity)
								dv.ubounds[dep_dim] -= shift_amount;
						}
					}
					j->second = dvs;
				}
		for (int i = 0; i < dep.vertex.size(); i++)
			if (stmt_nums.find(i) == stmt_nums.end())
				for (DependenceGraph::EdgeList::iterator j =
						dep.vertex[i].second.begin();
						j != dep.vertex[i].second.end(); j++)
					if (stmt_nums.find(j->first) != stmt_nums.end()) {
						// dependence from unshifted statement to shifted statement
						std::vector<DependenceVector> dvs = j->second;
						for (int k = 0; k < dvs.size(); k++) {
							DependenceVector &dv = dvs[k];
							if (dv.is_data_dependence()) {
								if (dv.lbounds[dep_dim] != -posInfinity)
									dv.lbounds[dep_dim] += shift_amount;
								if (dv.ubounds[dep_dim] != posInfinity)
									dv.ubounds[dep_dim] += shift_amount;
							}
						}
						j->second = dvs;
					}
	}
}

void Loop::scale(const std::set<int> &stmt_nums, int level, int scale_amount) {
	std::vector<int> skew_amount(level, 0);
	skew_amount[level - 1] = scale_amount;
	skew(stmt_nums, level, skew_amount);
}

void Loop::reverse(const std::set<int> &stmt_nums, int level) {
	scale(stmt_nums, level, -1);
}

void Loop::fuse(const std::set<int> &stmt_nums, int level) {
	if (stmt_nums.size() == 0 || stmt_nums.size() == 1)
		return;

	// invalidate saved codegen computation
	delete last_compute_cgr_;
	last_compute_cgr_ = NULL;
	delete last_compute_cg_;
	last_compute_cg_ = NULL;

	int dim = 2 * level - 1;
	// check for sanity of parameters
	std::vector<int> ref_lex;
	int ref_stmt_num;
	for (std::set<int>::const_iterator i = stmt_nums.begin();
			i != stmt_nums.end(); i++) {
		if (*i < 0 || *i >= stmt.size())
			throw std::invalid_argument(
					"invalid statement number " + to_string(*i));
		if (level <= 0
				|| (level > (stmt[*i].xform.n_out() - 1) / 2
						|| level > stmt[*i].loop_level.size()))
			throw std::invalid_argument(
					"invalid loop level " + to_string(level));
		if (ref_lex.size() == 0) {
			ref_lex = getLexicalOrder(*i);
			ref_stmt_num = *i;
		} else {
			std::vector<int> lex = getLexicalOrder(*i);
			for (int j = 0; j < dim - 1; j += 2)
				if (lex[j] != ref_lex[j])
					throw std::invalid_argument(
							"statements for fusion must be in the same level-"
									+ to_string(level - 1) + " subloop");
		}
	}

	// collect lexicographical order values from to-be-fused statements
	std::set<int> lex_values;
	for (std::set<int>::const_iterator i = stmt_nums.begin();
			i != stmt_nums.end(); i++) {
		std::vector<int> lex = getLexicalOrder(*i);
		lex_values.insert(lex[dim - 1]);
	}
	if (lex_values.size() == 1)
		return;
	// negative dependence would prevent fusion

	int dep_dim = get_dep_dim_of(ref_stmt_num, level);

	for (std::set<int>::iterator i = lex_values.begin(); i != lex_values.end();
			i++) {
		ref_lex[dim - 1] = *i;
		std::set<int> a = getStatements(ref_lex, dim - 1);
		std::set<int>::iterator j = i;
		j++;
		for (; j != lex_values.end(); j++) {
			ref_lex[dim - 1] = *j;
			std::set<int> b = getStatements(ref_lex, dim - 1);
			for (std::set<int>::iterator ii = a.begin(); ii != a.end(); ii++)
				for (std::set<int>::iterator jj = b.begin(); jj != b.end();
						jj++) {
					std::vector<DependenceVector> dvs;
					dvs = dep.getEdge(*ii, *jj);
					for (int k = 0; k < dvs.size(); k++)
						if (dvs[k].isCarried(dep_dim)
								&& dvs[k].hasNegative(dep_dim))
							throw loop_error(
									"loop error: statements " + to_string(*ii)
											+ " and " + to_string(*jj)
											+ " cannot be fused together due to negative dependence");
					dvs = dep.getEdge(*jj, *ii);
					for (int k = 0; k < dvs.size(); k++)
						if (dvs[k].isCarried(dep_dim)
								&& dvs[k].hasNegative(dep_dim))
							throw loop_error(
									"loop error: statements " + to_string(*jj)
											+ " and " + to_string(*ii)
											+ " cannot be fused together due to negative dependence");
				}
		}
	}

	std::set<int> same_loop = getStatements(ref_lex, dim - 3);

	std::vector < std::set<int> > s = sort_by_same_loops(same_loop, level);

	std::set<int> s1;
	std::set<int> s2;
	std::set<int> s4;
	std::vector < std::set<int> > s3;
	for (std::set<int>::iterator kk = stmt_nums.begin(); kk != stmt_nums.end();
			kk++)
		for (int i = 0; i < s.size(); i++)
			if (s[i].find(*kk) != s[i].end()) {
				s1.insert(s[i].begin(), s[i].end());
				s2.insert(i);
			}

	s3.push_back(s1);
	for (int i = 0; i < s.size(); i++)
		if (s2.find(i) == s2.end()) {
			s3.push_back(s[i]);
			s4.insert(s[i].begin(), s[i].end());
		}
	try {
		std::vector < std::set<int> > s5;
		s5.push_back(s1);
		s5.push_back(s4);

		//Dependence Check for Ordering Constraint
		//Graph<std::set<int>, bool> dummy = construct_induced_graph_at_level(s5,
		//      dep, dep_dim);

		Graph<std::set<int>, bool> g = construct_induced_graph_at_level(s3, dep,
				dep_dim);

		s = typed_fusion(g);
	} catch (const loop_error &e) {

		throw loop_error(
				"statements cannot be fused together due to negative dependence");

	}

	if (s3.size() == s.size()) {
		int order = 0;
		for (int i = 0; i < s.size(); i++) {

			for (std::set<int>::iterator it = s[i].begin(); it != s[i].end();
					it++) {

				assign_const(stmt[*it].xform, 2 * level - 2, order);

			}

			order++;
		}
	} else if (s3.size() > s.size()) {

		int order = 0;
		for (int j = 0; j < s.size(); j++) {
			std::set<int>::iterator it3;
			for (it3 = s1.begin(); it3 != s1.end(); it3++) {
				if (s[j].find(*it3) != s[j].end())
					break;
			}
			if (it3 != s1.end()) {
				for (std::set<int>::iterator it = s1.begin(); it != s1.end();
						it++)
					assign_const(stmt[*it].xform, 2 * level - 2, order);

				order++;

			}

			for (int i = 0; i < s3.size(); i++) {
				std::set<int>::iterator it2;

				for (it2 = s3[i].begin(); it2 != s3[i].end(); it2++) {
					if (s[j].find(*it2) != s[j].end())
						break;
				}

				if (it2 != s3[i].end()) {
					for (std::set<int>::iterator it = s3[i].begin();
							it != s3[i].end(); it++)
						assign_const(stmt[*it].xform, 2 * level - 2, order);

					order++;

				}
			}
		}

	} else
		throw loop_error("Typed Fusion Error");

}

void Loop::distribute(const std::set<int> &stmt_nums, int level) {
	if (stmt_nums.size() == 0 || stmt_nums.size() == 1)
		return;

	// invalidate saved codegen computation
	delete last_compute_cgr_;
	last_compute_cgr_ = NULL;
	delete last_compute_cg_;
	last_compute_cg_ = NULL;
	int dim = 2 * level - 1;
	int ref_stmt_num;
	// check for sanity of parameters
	std::vector<int> ref_lex;
	for (std::set<int>::const_iterator i = stmt_nums.begin();
			i != stmt_nums.end(); i++) {
		if (*i < 0 || *i >= stmt.size())
			throw std::invalid_argument(
					"invalid statement number " + to_string(*i));
		if (level < 1
				|| (level > (stmt[*i].xform.n_out() - 1) / 2
						|| level > stmt[*i].loop_level.size()))
			throw std::invalid_argument(
					"invalid loop level " + to_string(level));
		if (ref_lex.size() == 0) {
			ref_lex = getLexicalOrder(*i);
			ref_stmt_num = *i;
		} else {
			std::vector<int> lex = getLexicalOrder(*i);
			for (int j = 0; j <= dim - 1; j += 2)
				if (lex[j] != ref_lex[j])
					throw std::invalid_argument(
							"statements for distribution must be in the same level-"
									+ to_string(level) + " subloop");
		}
	}
	// find SCC in the to-be-distributed loop
	int dep_dim = get_dep_dim_of(ref_stmt_num, level);
	std::set<int> same_loop = getStatements(ref_lex, dim - 1);
	Graph<int, Empty> g;
	for (std::set<int>::iterator i = same_loop.begin(); i != same_loop.end();
			i++)
		g.insert(*i);
	for (int i = 0; i < g.vertex.size(); i++)
		for (int j = i + 1; j < g.vertex.size(); j++) {
			std::vector<DependenceVector> dvs;
			dvs = dep.getEdge(g.vertex[i].first, g.vertex[j].first);
			for (int k = 0; k < dvs.size(); k++)
				if (dvs[k].isCarried(dep_dim)) {
					g.connect(i, j);
					break;
				}
			dvs = dep.getEdge(g.vertex[j].first, g.vertex[i].first);
			for (int k = 0; k < dvs.size(); k++)
				if (dvs[k].isCarried(dep_dim)) {
					g.connect(j, i);
					break;
				}
		}
	std::vector < std::set<int> > s = g.topoSort();
	// find statements that cannot be distributed due to dependence cycle
	Graph<std::set<int>, Empty> g2;
	for (int i = 0; i < s.size(); i++) {
		std::set<int> t;
		for (std::set<int>::iterator j = s[i].begin(); j != s[i].end(); j++)
			if (stmt_nums.find(g.vertex[*j].first) != stmt_nums.end())
				t.insert(g.vertex[*j].first);
		if (!t.empty())
			g2.insert(t);
	}
	for (int i = 0; i < g2.vertex.size(); i++)
		for (int j = i + 1; j < g2.vertex.size(); j++)
			for (std::set<int>::iterator ii = g2.vertex[i].first.begin();
					ii != g2.vertex[i].first.end(); ii++)
				for (std::set<int>::iterator jj = g2.vertex[j].first.begin();
						jj != g2.vertex[j].first.end(); jj++) {
					std::vector<DependenceVector> dvs;
					dvs = dep.getEdge(*ii, *jj);
					for (int k = 0; k < dvs.size(); k++)
						if (dvs[k].isCarried(dep_dim)) {
							g2.connect(i, j);
							break;
						}
					dvs = dep.getEdge(*jj, *ii);
					for (int k = 0; k < dvs.size(); k++)
						if (dvs[k].isCarried(dep_dim)) {
							g2.connect(j, i);
							break;
						}
				}
	std::vector < std::set<int> > s2 = g2.topoSort();
	// nothing to distribute
	if (s2.size() == 1)
		throw loop_error(
				"loop error: no statement can be distributed due to dependence cycle");
	std::vector < std::set<int> > s3;
	for (int i = 0; i < s2.size(); i++) {
		std::set<int> t;
		for (std::set<int>::iterator j = s2[i].begin(); j != s2[i].end(); j++)
			std::set_union(t.begin(), t.end(), g2.vertex[*j].first.begin(),
					g2.vertex[*j].first.end(), inserter(t, t.begin()));
		s3.push_back(t);
	}
	// associate other affected statements with the right distributed statements
	for (std::set<int>::iterator i = same_loop.begin(); i != same_loop.end();
			i++)
		if (stmt_nums.find(*i) == stmt_nums.end()) {
			bool is_inserted = false;
			int potential_insertion_point = 0;
			for (int j = 0; j < s3.size(); j++) {
				for (std::set<int>::iterator k = s3[j].begin();
						k != s3[j].end(); k++) {
					std::vector<DependenceVector> dvs;
					dvs = dep.getEdge(*i, *k);
					for (int kk = 0; kk < dvs.size(); kk++)
						if (dvs[kk].isCarried(dep_dim)) {
							s3[j].insert(*i);
							is_inserted = true;
							break;
						}
					dvs = dep.getEdge(*k, *i);
					for (int kk = 0; kk < dvs.size(); kk++)
						if (dvs[kk].isCarried(dep_dim))
							potential_insertion_point = j;
				}
				if (is_inserted)
					break;
			}
			if (!is_inserted)
				s3[potential_insertion_point].insert(*i);
		}
	// set lexicographical order after distribution
	int order = ref_lex[dim - 1];
	shiftLexicalOrder(ref_lex, dim - 1, s3.size() - 1);
	for (std::vector<std::set<int> >::iterator i = s3.begin(); i != s3.end();
			i++) {
		for (std::set<int>::iterator j = (*i).begin(); j != (*i).end(); j++)
			assign_const(stmt[*j].xform, dim - 1, order);
		order++;
	}
	// no need to update dependence graph
	;
	return;
}

/*

 Developer : Theekshana Dilshan
 functionality : apply a user defined transformation on a statement

 */

void Loop::diamond_tile(int stmt_num, const std::vector<int> tile_sizes) {

	// check the validity of function arguments

	if (stmt_num < 0 || stmt_num >= stmt.size())
		throw std::invalid_argument("invalid statement " + to_string(stmt_num));

	if (tile_sizes.size() > num_dep_dim)
		throw std::invalid_argument(
				"invalid number of tiles " + to_string(tile_sizes.size()));

	// check the individual tile size in the set
	for (int i = 0; i < tile_sizes.size(); i++)
		if (tile_sizes[i] < 0)
			throw std::invalid_argument("invalid tile size");

	// extract the dependency in the program stmt_num

	std::vector<hyperPlane> dependencyVectors;

	for (DependenceGraph::EdgeList::iterator j =
			dep.vertex[stmt_num].second.begin();
			j != dep.vertex[stmt_num].second.end(); j++) {

		std::vector<DependenceVector> dvs = j->second;

		for (int k = 0; k < dvs.size(); k++) {

			// Programs with constant dependency distances

			if (dvs[k].type == DEP_W2R) {

				std::vector<int> depvector;

				for (int z = 0; z < dvs[k].lbounds.size(); z++) {

					omega::coef_t lbound = dvs[k].lbounds[z];
					omega::coef_t ubound = dvs[k].ubounds[z];

					if (lbound == ubound) {
						depvector.push_back(lbound);
					}

				}

				// create a new hyperplane object and add the vector
				hyperPlane hyperplane;
				hyperplane.depVector.setVector(depvector);
				dependencyVectors.push_back(hyperplane);

			}

		}
	}

	// Find the normal of the hyperplanes  h.d >= 0

	std::vector<Vector> validNormalHyperplanes;

	for (int i = 0; i < dependencyVectors.size(); i++) {

		Vector normal;
		normal.setVector(dependencyVectors[i].depVector.OrothognalVector());

		bool selected = true;

		for (int j = 0; j < dependencyVectors.size(); j++) {

			if (dependencyVectors[j].depVector.dotProduct(normal) < 0) {

				selected = false;
				break;
			}

		}

		if (selected) {

			validNormalHyperplanes.push_back(normal);

		}

	}

	// n-dimensional loop need to have n normal vectors

	if (validNormalHyperplanes.size() != num_dep_dim) {

		if (validNormalHyperplanes.size() > num_dep_dim) {

			// find the most optimal soltions

		} else {

		}

	}

	// define the tiling transformation using Omega

	int n = stmt[stmt_num].xform.n_out();

	omega::Relation r(n, 2 * n - 1);

	F_And *root = r.add_and();

	/* define
	 * [in1,in2,in3,in4,in5]->[out1,out2,out3,out4,in1,in2,in3,in4,in5]
	 *
	 */
	for (int i = 1; i <= n; i++) {

		EQ_Handle eq = root->add_EQ();
		eq.update_coef(r.output_var(n + i - 1), -1);
		eq.update_coef(r.input_var(i), 1);

	}

	/*
	 * [in1,in2,in3,in4,in5]->[0,out2,0,out4,in1,in2,in3,in4,in5]
	 *
	 */

	for (int i = 1; i < n; i += 2) {

		EQ_Handle eq = root->add_EQ();
		eq.update_coef(r.output_var(i), 1);
	}

	F_Exists *exist = root->add_exists();
	F_And *AndRel = exist->add_and();

	for (int i = 2; i < n; i += 2) {

		Variable_ID e = exist->declare();

		GEQ_Handle geq1 = AndRel->add_GEQ();
		geq1.update_coef(e, 1);

		GEQ_Handle geq2 = AndRel->add_GEQ();
		geq2.update_coef(e, -1);
		geq1.update_const(tile_sizes[i / 2 - 1] - 1);

		EQ_Handle eq = AndRel->add_EQ();
		eq.update_coef(r.output_var(i), tile_sizes[i / 2 - 1]);
		eq.update_coef(e, 1);

		// extract the selected hyperplanes
		std::vector<int> normal = validNormalHyperplanes[i / 2 - 1].getVector();

		for (int j = 2; j < n; j += 2) {

			eq.update_coef(r.input_var(j), -normal[j / 2 - 1]);

		}

	}

	r.print();

	omega::Relation sch(2 * n - 1, 2 * n - 1);
	F_And *sch_root = sch.add_and();

	for (int i = 1; i < 2 * n; i++) {

		if (i != 2) {

			EQ_Handle eq = sch_root->add_EQ();
			eq.update_coef(sch.input_var(i), -1);
			eq.update_coef(sch.output_var(i), 1);

		}

	}

	EQ_Handle schEQ = sch_root->add_EQ();
	schEQ.update_coef(sch.output_var(2), 1);
	for (int i = 2; i < n; i += 2) {

		schEQ.update_coef(sch.input_var(i), -1);

	}

	stmt[stmt_num].xform = Composition(r, stmt[stmt_num].xform);
	stmt[stmt_num].xform = Composition(sch, stmt[stmt_num].xform);

	stmt[stmt_num].xform.simplify();
	stmt[stmt_num].xform.print();

	/*	for (DependenceGraph::EdgeList::iterator j =
	 dep.vertex[stmt_num].second.begin(); j != dep.vertex[stmt_num].second.end();
	 j++) {

	 std::vector<DependenceVector> dvs = j->second;

	 for (int k = 0; k < dvs.size(); k++) {

	 long long dpdncy = 0;
	 coef_t lb;

	 for (int it = 0; it < validNormalHyperplanes.size(); it++) {

	 dpdncy = dependencyVectors[k].depVector.dotProduct_v2(
	 validNormalHyperplanes[it]);

	 lb = dpdncy;

	 dvs[k].lbounds[it] = lb;
	 dvs[k].ubounds[it] = lb;
	 }

	 }

	 j->second = dvs;
	 } */

}

void Loop::testFunction() {

	// tile the external loop

	omega::Relation r(5, 7);

	F_And *root = r.add_and();

	EQ_Handle eq0 = root->add_EQ();
	eq0.update_coef(r.output_var(1), 1);

	for (int i = 1; i <= 5; i++) {

		EQ_Handle eq = root->add_EQ();
		eq.update_coef(r.output_var(i + 2), -1);
		eq.update_coef(r.input_var(i), 1);
	}

	F_Exists *exist = root->add_exists();

	Variable_ID t1 = exist->declare("t1");
	F_And *EAnd = exist->add_and();

	EQ_Handle Eeq1 = EAnd->add_EQ();
	Eeq1.update_coef(t1, -4);
	Eeq1.update_coef(r.output_var(2), 1);

	GEQ_Handle Egeq1 = EAnd->add_GEQ();
	Egeq1.update_coef(t1, 1);

	GEQ_Handle Egeq2 = EAnd->add_GEQ();
	Egeq2.update_coef(r.output_var(4), 1);
	Egeq2.update_coef(r.output_var(2), -1);

	GEQ_Handle Egeq3 = EAnd->add_GEQ();
	Egeq3.update_coef(r.output_var(4), -1);
	Egeq3.update_coef(r.output_var(2), 1);
	Egeq3.update_const(3);

	stmt[0].xform.print();
	stmt[0].xform = Composition(r, stmt[0].xform);
	stmt[0].xform.simplify();
	stmt[0].xform.print();

//	std::vector < std::vector<int> > *depVectors;

	/*for (int i = 0; i < dep.vertex.size(); i++) {

	 for (DependenceGraph::EdgeList::iterator j =
	 dep.vertex[i].second.begin(); j != dep.vertex[i].second.end();
	 j++) {

	 std::vector<DependenceVector> dvs = j->second;

	 //depVectors = new std::vector<std::vector<int> >(dvs.size());

	 std::cout << " printf the dependecies";
	 for (int k = 0; k < dvs.size(); k++) {

	 std::cout << dvs[k].type;

	 std::cout << "dependency=(";
	 for (int z = 0; z < dvs[k].lbounds.size(); z++) {

	 omega::coef_t lbound = dvs[k].lbounds[z];
	 omega::coef_t ubound = dvs[k].ubounds[z];

	 std::cout << lbound << " " << ubound << " ";


	 }

	 std::cout << ")\n";

	 }
	 }

	 } */

	/*for (int a = 0; a < (*depVectors).size(); a++) {

	 for (int b = 0; b < (*depVectors)[a].size(); b++)
	 std::cout << (*depVectors)[a][b];

	 std::cout << std::endl;
	 }

	 std::vector < std::vector<int> > hyperplanes(2);
	 hyperplanes = get_perpendicular_hyperplanes(
	 get_widest_vectors(*depVectors));
	 //vec2 = get_widest_vectors(vec);

	 std::cout << "value of vec (" << hyperplanes[0][0] << ", "
	 << hyperplanes[0][1] << ")\n" << std::endl;
	 std::cout << "value of vec (" << hyperplanes[1][0] << ", "
	 << hyperplanes[1][1] << ")\n" << std::endl;

	 //change the itertion space using omega

	 for (int i = 0; i < stmt.size(); i++) {

	 int n = stmt[i].xform.n_out();
	 omega::Relation r(n, n);

	 F_And *root = r.add_and();
	 int k = 0;
	 for (int j = 1; j <= n; j++) {  // for each element in the relation

	 EQ_Handle eq = root->add_EQ(); // add a equation

	 if (j % 2 == 0) {

	 // at each loop level , multiply with the
	 int rl = 2;

	 for (int ele = 0; ele < hyperplanes[k].size(); ele++, rl += 2) {

	 eq.update_coef(r.input_var(rl), -hyperplanes[k][ele]);

	 }

	 eq.update_coef(r.output_var(j), 1);
	 k++;

	 } else { // at auxilary loop levels

	 eq.update_coef(r.input_var(j), 1);
	 eq.update_coef(r.output_var(j), -1);

	 }

	 }

	 stmt[i].xform = Composition(r, stmt[i].xform);
	 stmt[i].xform.simplify();

	 }

	 //update the dependency graph before
	 for (int i = 0; i < dep.vertex.size(); i++) {

	 for (DependenceGraph::EdgeList::iterator j =
	 dep.vertex[i].second.begin(); j != dep.vertex[i].second.end();
	 j++) {

	 std::vector<DependenceVector> dvs = j->second;

	 for (int k = 0; k < dvs.size(); k++) {

	 for (int z = 0; z < dvs[k].lbounds.size(); z++) {

	 long long dpdncy = 0;

	 for (int it = 0; it < hyperplanes.size(); it++) {

	 for (int in = 0; in < hyperplanes[it].size(); in++) {

	 dpdncy += hyperplanes[it][in]
	 * (*depVectors)[z][in];

	 }

	 }

	 std::cout << dpdncy << " ";

	 }

	 }
	 }

	 }   */

	return;
}

omega::Relation Loop::tiledRelation(omega::Relation sch, omega::Relation v,
		omega::Relation &xform) {

	omega::Relation r(5, 9);
	F_And *root = r.add_and();
	EQ_Handle eq0 = root->add_EQ();
	eq0.update_coef(r.output_var(1), 1);

	EQ_Handle eq02 = root->add_EQ();
	eq02.update_coef(r.output_var(3), 1);

	for (int i = 1; i <= 5; i++) {

		EQ_Handle eq = root->add_EQ();
		eq.update_coef(r.output_var(i + 4), -1);
		eq.update_coef(r.input_var(i), 1);
	}

	F_Exists *exist = root->add_exists();

	Variable_ID t1 = exist->declare("t1");
	F_And *EAnd = exist->add_and();

	EQ_Handle Eeq1 = EAnd->add_EQ();
	Eeq1.update_coef(t1, -4);
	Eeq1.update_coef(r.output_var(2), 1);

	GEQ_Handle Egeq1 = EAnd->add_GEQ();
	Egeq1.update_coef(t1, 1);

	GEQ_Handle Egeq2 = EAnd->add_GEQ();
	Egeq2.update_coef(r.output_var(6), 1);
	Egeq2.update_coef(r.output_var(2), -1);

	GEQ_Handle Egeq3 = EAnd->add_GEQ();
	Egeq3.update_coef(r.output_var(6), -1);
	Egeq3.update_coef(r.output_var(2), 1);
	Egeq3.update_const(3);

	//F_Exists *exist = root->add_exists();

	Variable_ID t2 = exist->declare("t2");

	EQ_Handle Eeq4 = EAnd->add_EQ();
	Eeq4.update_coef(t2, -32);
	Eeq4.update_coef(r.output_var(4), 1);

	GEQ_Handle Egeq5 = EAnd->add_GEQ();
	Egeq5.update_coef(t2, 1);

	GEQ_Handle Egeq6 = EAnd->add_GEQ();
	Egeq6.update_coef(r.output_var(8), 1);
	Egeq6.update_coef(r.output_var(4), -1);

	GEQ_Handle Egeq7 = EAnd->add_GEQ();
	Egeq7.update_coef(r.output_var(8), -1);
	Egeq7.update_coef(r.output_var(4), 1);
	Egeq7.update_const(31);

	r.simplify();
	r.print();

//	xform = Composition(v, xform);
	xform = Composition(sch, xform);
	xform = Composition(r, xform);

	//omega::Relation fn = Composition(r,sch)	;
	//omega::Relation gn = Composition(fn,v)	;
	//xform = Composition(gn,xform)	;
	//gn.simplify();
	//gn.print();
	return r;
}

void Loop::dTile() {

	delete last_compute_cgr_;
	last_compute_cgr_ = NULL;
	delete last_compute_cg_;
	last_compute_cg_ = NULL;

	// Saves all the direct dependencies in the source code
	std::vector<hyperPlane> *depVectors;

	for (int i = 0; i < dep.vertex.size(); i++) {
		for (DependenceGraph::EdgeList::iterator j =
				dep.vertex[i].second.begin(); j != dep.vertex[i].second.end();
				j++) {

			std::vector<DependenceVector> dvs = j->second;

			depVectors = new std::vector<hyperPlane>(dvs.size());
			int truedep = 0;

			for (int k = 0; k < dvs.size(); k++) {

				// if it's a true dependency
				if (dvs[k].type == DEP_W2R) {

					std::vector<int> depvector;

					for (int z = 0; z < dvs[k].lbounds.size(); z++) {

						omega::coef_t lbound = dvs[k].lbounds[z];
						omega::coef_t ubound = dvs[k].ubounds[z];

						// we consider only this condition in the dependency selection
						// this condition will change
						if (lbound == ubound) {

							//(*depVectors)[truedep].depVector.addElements(lbound) ;
							depvector.push_back(lbound);

						}

					}

					// add to the dependency data struture
					(*depVectors)[truedep].depVector.setVector(depvector);

				}
				truedep++;

			}
		}

	}

	// For all the dependencies found find the normal vector
	for (int i = 0; i < (*depVectors).size(); i++) {

		(*depVectors)[i].depVector.print();
		(*depVectors)[i].orthoVector.setVector(
				(*depVectors)[i].depVector.OrothognalVector());
		(*depVectors)[i].orthoVector.print();

		//	(*depVectors)[i].printOrtho();

	}

	// For any normal hyperplane (h) and with any dependency d
	// h.d >= 0 has to be satisfied
	std::vector<int> impossibleNormalDependencies;

	for (int i = 0; i < (*depVectors).size(); i++) {

		for (int j = 0; j < (*depVectors).size(); j++) {

			if ((*depVectors)[i].depVector.dotProduct(
					(*depVectors)[j].orthoVector) < 0)
				impossibleNormalDependencies.push_back(j);

		}

		//	(*depVectors)[i].printOrtho();

	}

	// Find the hyperplanes that can be used to slice the iteration space
	// only generic implementation is found here,
	// we need to consider optimal hyperplanes from all the set of hyperplanes

	std::vector<Vector> selectedhyperplanes;

	std::cout << "\nselected hyperplane normals\n";
	for (int i = 0; i < (*depVectors).size(); i++) {
		bool possible = true;
		for (int j = 0; j < impossibleNormalDependencies.size(); j++) {

			if (i == impossibleNormalDependencies[j])
				possible = false;
		}

		if (possible) {

			(*depVectors)[i].orthoVector.print();
			selectedhyperplanes.push_back((*depVectors)[i].orthoVector);

		}
	}

	// apply the transformatin using Omega

	for (int i = 0; i < stmt.size(); i++) {

		int n = stmt[i].xform.n_out();
		omega::Relation r(n, n);

		F_And *root = r.add_and();
		int k = 0;
		for (int j = 1; j <= n; j++) {  // for each element in the relation

			EQ_Handle eq = root->add_EQ(); // add a equation

			if (j % 2 == 0) {

				// by following the CHiLL relation model
				// [c1,l1,c2,l2,.....,cn-1,ln-1,cn,ln]
				// we need to consider l1,l2,...,ln for transformation
				int rl = 2;
				eq.update_coef(r.output_var(j), -1);

				std::vector<int> normal = selectedhyperplanes[k].getVector();

				for (int ele = 0; ele < normal.size(); ele++, rl += 2) {

					eq.update_coef(r.input_var(rl), normal[ele]);

				}
				k++;

			} else { // at auxiliary loop levels
				eq.update_coef(r.input_var(j), 1);
				eq.update_coef(r.output_var(j), -1);

			}

		}

		omega::Relation schedule(n, n);

		F_And *Scroot = schedule.add_and();
		for (int j = 1; j <= n; j++) {  // for each element in the relation

			EQ_Handle eq = Scroot->add_EQ(); // add a equation

			if (j == 2) {

				//	eq.update_coef(schedule.output_var(j), -1);
				F_Exists *exist = Scroot->add_exists();
				F_And *AndRelation = exist->add_and();

				Variable_ID e = exist->declare();
				EQ_Handle eq0 = AndRelation->add_EQ();
				eq0.update_coef(e, 1);
				for (int ele = 1; ele <= n; ele++) {

					eq0.update_coef(schedule.input_var(ele), -1);

				}

				EQ_Handle eq1 = AndRelation->add_EQ();
				eq1.update_coef(schedule.output_var(j), -1);
				eq1.update_coef(e, 1);

			} else { // at auxiliary loop levels

				eq.update_coef(schedule.input_var(j), 1);
				eq.update_coef(schedule.output_var(j), -1);

			}

		}

		std::cout << std::endl;
		//	omega::Relation f = tiledRelation(schedule, r, stmt[i].xform);
		schedule.print();

		std::cout << std::endl;
		stmt[i].xform = Composition(r, stmt[i].xform);
		stmt[i].xform = Composition(schedule, stmt[i].xform);
		stmt[i].xform.simplify();
		stmt[i].xform.print();

	}

	//update the dependency graph before applying tiling to the transformed iteration space

	for (int i = 0; i < dep.vertex.size(); i++) {

		for (DependenceGraph::EdgeList::iterator j =
				dep.vertex[i].second.begin(); j != dep.vertex[i].second.end();
				j++) {

			std::vector<DependenceVector> dvs = j->second;

			for (int k = 0; k < dvs.size(); k++) {

				long long dpdncy = 0;
				coef_t lb;

				for (int it = 0; it < selectedhyperplanes.size(); it++) {

					dpdncy = (*depVectors)[k].depVector.dotProduct_v2(
							selectedhyperplanes[it]);

					lb = dpdncy;

					dvs[k].lbounds[it] = lb;
					dvs[k].ubounds[it] = lb;
				}

			}

			j->second = dvs;
		}

	}

	// define the time schedule to the omega transformation

	/*for (int i = 0; i < stmt.size(); i++) {

	 int n = stmt[i].xform.n_out();
	 omega::Relation r(n, n);

	 F_And *root = r.add_and();
	 for (int j = 1; j <= n; j++) {  // for each element in the relation

	 EQ_Handle eq = root->add_EQ(); // add a equation

	 if (j == 2) {

	 eq.update_coef(r.output_var(j), -1);

	 for (int ele = 1; ele <= n; ele++) {

	 eq.update_coef(r.input_var(ele), 1);

	 }

	 } else { // at auxiliary loop levels

	 eq.update_coef(r.input_var(j), 1);
	 eq.update_coef(r.output_var(j), -1);

	 }

	 }

	 stmt[i].xform = Composition(r, stmt[i].xform);
	 stmt[i].xform.simplify();
	 stmt[i].xform.print();  // altered relation

	 }  */

	// print the new dependencies
	for (int i = 0; i < dep.vertex.size(); i++) {

		for (DependenceGraph::EdgeList::iterator j =
				dep.vertex[i].second.begin(); j != dep.vertex[i].second.end();
				j++) {

			std::vector<DependenceVector> dvs = j->second;

			std::cout << " printf the dependecies";
			for (int k = 0; k < dvs.size(); k++) {

				std::cout << dvs[k].type;

				std::cout << "dependency=(";
				for (int z = 0; z < dvs[k].lbounds.size(); z++) {

					omega::coef_t lbound = dvs[k].lbounds[z];
					omega::coef_t ubound = dvs[k].ubounds[z];

					if (lbound == ubound) {
						std::cout << lbound << " ";

					}

				}

				std::cout << ")\n";

			}
		}

	}
	//std::cout << "\nafter tiling\n" ;
	//stmt[0].xform.simplify();
	//stmt[0].xform.print();

//	tile(0,1,32) ;
//	tile(0,3,32) ;

}

// tile the loop level given by level parameter

/**
 This method is to find out outer most dependency vectors.
 */
std::vector<std::vector<int> > Loop::get_widest_vectors(
		std::vector<std::vector<int> > vec) {

	double clockwise_angle_from_x = 0.0;
	double max_clockwise_angle_from_x = 0.0;
	double min_clockwise_angle_from_x = 0.0;

	std::vector < std::vector<int> > selected_vectors(2);

	for (int i = 0; i < vec.size(); i++) {
		clockwise_angle_from_x = atan2(vec[i][0], vec[i][1]) * 180 / PI;

		if (i == 0) {
			max_clockwise_angle_from_x = clockwise_angle_from_x;
			min_clockwise_angle_from_x = clockwise_angle_from_x;

			selected_vectors[0].push_back(vec[0][0]);
			selected_vectors[0].push_back(vec[0][1]); // represent the vector which makes largest angle from x axis.
			selected_vectors[1].push_back(vec[0][0]); // represent the vector which makes smallest angle from x axis.
			selected_vectors[1].push_back(vec[0][1]);
		}

		if (max_clockwise_angle_from_x < clockwise_angle_from_x) {

			max_clockwise_angle_from_x = clockwise_angle_from_x;
			selected_vectors[0].pop_back();
			selected_vectors[0].pop_back();
			selected_vectors[0].push_back(vec[i][0]);
			selected_vectors[0].push_back(vec[i][1]);
		}

		if (min_clockwise_angle_from_x > clockwise_angle_from_x) {

			min_clockwise_angle_from_x = clockwise_angle_from_x;
			selected_vectors[1].pop_back();
			selected_vectors[1].pop_back();
			selected_vectors[1].push_back(vec[i][0]);
			selected_vectors[1].push_back(vec[i][1]);

		}
	}
	return selected_vectors;
}

/**
 This methode returns two hyperplanes which are perpendicular to given two vectors.
 */
std::vector<std::vector<int> > Loop::get_perpendicular_hyperplanes(
		std::vector<std::vector<int> > vec) {

	std::vector < std::vector<int> > perpendicular_hyperplanes(2);

	int max_x = vec[0][0];
	int max_y = vec[0][1];
	int min_x = vec[1][0];
	int min_y = vec[1][1];

	int h_max_x;
	int h_max_y;
	int h_min_x;
	int h_min_y;

	if (((atan2(vec[0][0], vec[0][1]) - atan2(vec[1][0], vec[1][1])) * 180 / PI)
			> 90.001) {
		h_max_x = abs(max_y);
		h_max_y = -(max_x * h_max_x) / max_y;

		h_min_x = abs(min_y);
		h_min_y = -(min_x * h_min_x) / min_y;

		perpendicular_hyperplanes[0].push_back(h_max_x);
		perpendicular_hyperplanes[0].push_back(h_max_y);
		perpendicular_hyperplanes[1].push_back(h_min_x);
		perpendicular_hyperplanes[1].push_back(h_min_y);

	} else {

		perpendicular_hyperplanes[0].push_back(min_x);
		perpendicular_hyperplanes[0].push_back(min_y);

		h_min_x = abs(min_y);
		h_min_y = -(min_x * h_min_x) / min_y;
		perpendicular_hyperplanes[1].push_back(h_min_x);
		perpendicular_hyperplanes[1].push_back(h_min_y);

	}

	return perpendicular_hyperplanes;
}

Vector::Vector(std::vector<int> &v) {

	vec = v;
}

void Vector::addElements(int xi) {

	vec.push_back(xi);

}

void Vector::setVector(std::vector<int> v) {

	vec = v;

}

std::vector<int> Vector::getVector() {

	return vec;

}

float Vector::euclidianDistance() {

	float dis = 0;
	for (int i = 0; i < vec.size(); i++) {

		dis += pow(vec[i], 2);
	}

	return sqrt(dis);

}

int Vector::dimension() {

	return vec.size();
}

void Vector::print() {

	std::cout << "(";
	for (int i = 0; i < vec.size() - 1; i++)
		std::cout << vec[i] << ",";

	std::cout << vec[vec.size() - 1] << ")";

}

std::vector<int> Vector::OrothognalVector() {

// algorithm to find orthogonal vector is implemented here

	std::vector<int> orthovector;

	int size = vec.size();

	int lastele = vec[size - 1];

	if (lastele != 0) {

		for (int i = 0; i < size; i++) {

			int t = lastele;
			if (i == size - 1) {

				t = 0;
				for (int j = 0; j < size - 1; j++)
					t += -vec[j];

			}

			t = lastele > 0 ? t : -t;
			orthovector.push_back(t);
		}

	} else {

		for (int i = 0; i < size - 1; i++)
			orthovector.push_back(0);
		orthovector.push_back(1);

	}

	return orthovector;

}

float Vector::dotProduct(Vector v) {

	if (v.dimension() != this->dimension())
		return -4500;
	else {

		float dotprd = 0;
		std::vector<int> v_2 = v.getVector();

		for (int i = 0; i < this->dimension(); i++) {

			dotprd += v_2[i] * vec[i];
		}

		return dotprd / v.euclidianDistance();

	}

}

int Vector::dotProduct_v2(Vector v) {

	if (v.dimension() != this->dimension())
		return -4500;
	else {

		float dotprd = 0;
		std::vector<int> v_2 = v.getVector();

		for (int i = 0; i < this->dimension(); i++) {

			dotprd += v_2[i] * vec[i];
		}

		return dotprd;

	}

}

