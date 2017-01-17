/*


   Diamond Tiling 
   Author : Theekshana Dilsha

*/


#include <codegen.h>
#include "loop.hh"
#include "omegatools.hh"
#include "ir_code.hh"
#include "chill_error.hh"

using namespace omega;
void Loop::diamond_tile(int stmt_num, const std::set<int> tile_sizes) {

	// check the validity of function arguments

	if (stmt_num < 0 || stmt_num >= stmt.size())
		throw std::invalid_argument("invalid statement " + to_string(stmt_num));

	if (tile_sizes.size() > num_dep_dim)
		throw std::invalid_argument(
				"invalid number of tiles " + to_string(tile_sizes.size()));

	// check the individual tile size in the set
	for (std::set<int>::iterator i = tile_sizes.begin(); i != tile_sizes.end();
			i++)
		if (*i < 0)
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

	// Find the normal of the hyperplanes

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

	Relation xform_temp = stmt[stmt_num].xform;

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
		geq1.update_const(31);

		EQ_Handle eq = AndRel->add_EQ();
		eq.update_coef(r.output_var(i), 32);
		eq.update_coef(e, 1);

		// extract the selected hyperplanes
		std::vector<int> normal = validNormalHyperplanes[i/2-1].getVector();

		for (int j = 2; j < n; j += 2) {

			eq.update_coef(r.input_var(j), -normal[j/2-1] );

		}

	}

	r.print();

	/*

	 F_Exists *exist = root->add_exists();
	 Variable_ID e = exist->declare();

	 F_And *AndRel = exist->add_and();

	 GEQ_Handle geq1 = AndRel->add_GEQ();
	 geq1.update_coef(e, 1);

	 GEQ_Handle geq2 = AndRel->add_GEQ();
	 geq2.update_coef(e, -1);
	 geq1.update_const(31);

	 EQ_Handle eq = AndRel->add_EQ();
	 eq.update_coef(r.output_var(2), 32);
	 eq.update_coef(e, 1);
	 eq.update_coef(r.input_var(2), -2);
	 eq.update_coef(r.input_var(4), 1);

	 Variable_ID e2 = exist->declare();


	 GEQ_Handle geqi = AndRel->add_GEQ();
	 geqi.update_coef(e2, 1);

	 GEQ_Handle geqii = AndRel->add_GEQ();
	 geqii.update_coef(e2, -1);
	 geqii.update_const(31);

	 EQ_Handle eq2 = AndRel->add_EQ();
	 eq2.update_coef(r.output_var(4), 32);
	 eq2.update_coef(e2, 1);
	 eq2.update_coef(r.input_var(2), -2);
	 eq2.update_coef(r.input_var(4), -1);

	 r.print();  */

	stmt[stmt_num].xform = Composition(r, stmt[stmt_num].xform);
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


