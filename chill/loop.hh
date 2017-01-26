#ifndef LOOP_HH
#define LOOP_HH

#include <omega.h>
#include <codegen.h>
#include <code_gen/CG.h>
#include <vector>
#include <map>
#include <set>
#include<algorithm>
#include<iterator>
#include "dep.hh"
#include "ir_code.hh"
#include "irtools.hh"

// Project HiperTilings
#include<math.h>

#define PI 3.14159265

class IR_Code;
class Vector;
class hyperPlane;

enum TilingMethodType {
	StridedTile, CountedTile
};
enum LoopLevelType {
	LoopLevelOriginal, LoopLevelTile, LoopLevelUnknown
};

// Describes properties of each loop level of a statement. "payload"
// for LoopLevelOriginal means iteration space dimension, for
// LoopLevelTile means tiled loop level.  Special value -1 for
// LoopLevelTile means purely derived loop. For dependence dimension
// payloads, the values must be in an increasing order.
// "parallel_level" will be used by code generation to support
// multi-level parallelization (default 0 means sequential loop under
// the current parallelization level).
struct LoopLevel {
	LoopLevelType type;
	int payload;
	int parallel_level;
};

struct Statement {
	omega::CG_outputRepr *code;
	omega::Relation IS;
	omega::Relation xform;
	/*

	 lexigraphical order
	 when there are imperfect loop nest
	 nesting level

	 */
	std::vector<LoopLevel> loop_level;
	ir_tree_node *ir_stmt_node;
	//protonu--temporarily putting this back here
	//omega::Tuple<int> nonSplitLevels;
	//end--protonu.
};

class Loop {
protected:
	int tmp_loop_var_name_counter;
	static const std::string tmp_loop_var_name_prefix;
	int overflow_var_name_counter;
	static const std::string overflow_var_name_prefix;
	std::vector<int> stmt_nesting_level_;
	std::vector<std::string> index;
	std::map<int, omega::CG_outputRepr *> replace;

public:
	IR_Code *ir;
	std::vector<omega::Free_Var_Decl*> freevar;
	std::vector<Statement> stmt;
	std::vector<ir_tree_node *> ir_stmt;
	std::vector<ir_tree_node *> ir_tree;
	DependenceGraph dep;
	int num_dep_dim;
	omega::Relation known;
	omega::CG_outputRepr *init_code;
	omega::CG_outputRepr *cleanup_code;
	std::map<int, std::vector<omega::Free_Var_Decl *> > overflow;

protected:
	mutable omega::CodeGen *last_compute_cg_;
	mutable omega::CG_result *last_compute_cgr_;
	mutable int last_compute_effort_;

protected:
	bool init_loop(std::vector<ir_tree_node *> &ir_tree,
			std::vector<ir_tree_node *> &ir_stmt);
	int get_dep_dim_of(int stmt, int level) const;
	int get_last_dep_dim_before(int stmt, int level) const;
	std::vector<omega::Relation> getNewIS() const;
	omega::Relation getNewIS(int stmt_num) const;
	std::vector<int> getLexicalOrder(int stmt_num) const;
	int getLexicalOrder(int stmt_num, int level) const;
	std::set<int> getStatements(const std::vector<int> &lex, int dim) const;
	void shiftLexicalOrder(const std::vector<int> &lex, int dim, int amount);
	void setLexicalOrder(int dim, const std::set<int> &active,
			int starting_order = 0,
			std::vector<std::vector<std::string> > idxNames = std::vector<
					std::vector<std::string> >());
	void apply_xform(int stmt_num);
	void apply_xform(std::set<int> &active);
	void apply_xform();
	std::set<int> getSubLoopNest(int stmt_num, int level) const;

public:
	Loop() {
		ir = NULL;
		tmp_loop_var_name_counter = 1;
		init_code = NULL;
	}
	Loop(const IR_Control *control);
	~Loop();

	omega::CG_outputRepr *getCode(int effort = 1) const;
	void printCode(int effort = 1) const;
	void addKnown(const omega::Relation &cond);
	void print_internal_loop_structure() const;
	bool isInitialized() const;
	int num_statement() const {
		return stmt.size();
	}
	void printIterationSpace() const;
	void printDependenceGraph() const;
	void removeDependence(int stmt_num_from, int stmt_num_to);
	void dump() const;

	std::vector<std::set<int> > sort_by_same_loops(std::set<int> active,
			int level);
	//
	// legacy unimodular transformations for perfectly nested loops
	// e.g. M*(i,j)^T = (i',j')^T or M*(i,j,1)^T = (i',j')^T
	//
	bool nonsingular(const std::vector<std::vector<int> > &M);

	//
	// high-level loop transformations
	//
	void permute(const std::set<int> &active, const std::vector<int> &pi);
	void permute(int stmt_num, int level, const std::vector<int> &pi);
	void permute(const std::vector<int> &pi);
	void original();

	void tile(int stmt_num, int level, int tile_size, int outer_level = 1,
			TilingMethodType method = StridedTile, int alignment_offset = 0,
			int alignment_multiple = 1);
	std::set<int> split(int stmt_num, int level, const omega::Relation &cond);
	std::set<int> unroll(int stmt_num, int level, int unroll_amount,
			std::vector<std::vector<std::string> > idxNames = std::vector<
					std::vector<std::string> >(), int cleanup_split_level = 0);

	bool datacopy(
			const std::vector<std::pair<int, std::vector<int> > > &array_ref_nums,
			int level, bool allow_extra_read = false,
			int fastest_changing_dimension = -1, int padding_stride = 1,
			int padding_alignment = 4, int memory_type = 0);
	bool datacopy(int stmt_num, int level, const std::string &array_name,
			bool allow_extra_read = false, int fastest_changing_dimension = -1,
			int padding_stride = 1, int padding_alignment = 4, int memory_type =
					0);
	bool datacopy_privatized(int stmt_num, int level,
			const std::string &array_name,
			const std::vector<int> &privatized_levels, bool allow_extra_read =
					false, int fastest_changing_dimension = -1,
			int padding_stride = 1, int padding_alignment = 1, int memory_type =
					0);
	bool datacopy_privatized(
			const std::vector<std::pair<int, std::vector<int> > > &array_ref_nums,
			int level, const std::vector<int> &privatized_levels,
			bool allow_extra_read = false, int fastest_changing_dimension = -1,
			int padding_stride = 1, int padding_alignment = 1, int memory_type =
					0);
	bool datacopy_privatized(
			const std::vector<std::pair<int, std::vector<IR_ArrayRef *> > > &stmt_refs,
			int level, const std::vector<int> &privatized_levels,
			bool allow_extra_read, int fastest_changing_dimension,
			int padding_stride, int padding_alignment, int memory_type = 0);
	//std::set<int> scalar_replacement_inner(int stmt_num);

	Graph<std::set<int>, bool> construct_induced_graph_at_level(
			std::vector<std::set<int> > s, DependenceGraph dep, int dep_dim);
	std::vector<std::set<int> > typed_fusion(Graph<std::set<int>, bool> g);
	void fuse(const std::set<int> &stmt_nums, int level);
	void distribute(const std::set<int> &stmt_nums, int level);
	void skew(const std::set<int> &stmt_nums, int level,
			const std::vector<int> &skew_amount);
	void shift(const std::set<int> &stmt_nums, int level, int shift_amount);
	void scale(const std::set<int> &stmt_nums, int level, int scale_amount);
	void reverse(const std::set<int> &stmt_nums, int level);
	void peel(int stmt_num, int level, int peel_amount = 1);
	//
	// more fancy loop transformations
	//
	void modular_shift(int stmt_num, int level, int shift_amount) {
	}
	void diagonal_map(int stmt_num, const std::pair<int, int> &levels,
			int offset) {
	}
	void modular_partition(int stmt_num, int level, int stride) {
	}

	//
	// derived loop transformations
	//
	void shift_to(int stmt_num, int level, int absolute_position);
	std::set<int> unroll_extra(int stmt_num, int level, int unroll_amount,
			int cleanup_split_level = 0);
	bool is_dependence_valid_based_on_lex_order(int i, int j,
			const DependenceVector &dv, bool before);
	//
	// other public operations
	//
	void pragma(int stmt_num, int level, const std::string &pragmaText);
	void prefetch(int stmt_num, int level, const std::string &arrName,
			int hint);
	//void prefetch(int stmt_num, int level, const std::string &arrName, const std::string &indexName, int offset, int hint);

	// test transformation
	// Date: 11/08/16
	// Project_group : HiperTilings
	// developer : Theekshana Dilshan

	void testFunction();
	void diamondTiling(int stmt_num, const std::set<int> loops,
			const std::set<int> size);
	void dTile();
	void diamond_tile(int stmt, const std::vector<int> tile_sizes);

	std::vector<Vector> getDependencies(int stmt_num);
	std::vector<Vector> selectHyperplanes(std::vector<Vector> );
	std::vector<int>  orthogonalVector(std::vector<int> ) ;



	omega::Relation tiledRelation(omega::Relation , omega::Relation , omega::Relation &);

	std::vector<std::vector<int> > get_perpendicular_hyperplanes(
			std::vector<std::vector<int> > vec);
	std::vector<std::vector<int> > get_widest_vectors(
			std::vector<std::vector<int> > vec);

};

// vector class

class Vector {

private:
	std::vector<int> vec;

public:

	Vector(std::vector<int> &v);

	Vector() {};
	void addElements(int xi);
	bool setVector(std::vector<int> v) ;
	std::vector<int> getVector() const;
	float euclidianDistance() ;
	int dimension() const;
	void print() ;
	std::vector<int> OrothognalVector() ;
	float dotProduct(Vector v) ;
	int   dotProduct_v2(Vector v) ;
	bool operator<(  const Vector &anothervec ) const ;
	bool operator==(const Vector &anothervec) const ;


};

class hyperPlane {

public:
	Vector depVector;
	Vector orthoVector;

};

// class to save the depend
class hyperPlanes {

private:
	std::vector<int> depvector;      // dependency vector
	std::vector<int> orthovector; // perpendicular vector
	int size;
	float eculd;
public:
	void addValues(int xi) {

		depvector.push_back(xi);

	}

	std::vector<int> OrothognalVector() {

		// algorithm to find orthogonal vector is implemented here

		int size = depvector.size();

		int lastele = depvector[size - 1];

		if (lastele != 0) {

			for (int i = 0; i < size; i++) {

				int t = lastele;
				if (i == size - 1) {

					t = 0;
					for (int j = 0; j < size - 1; j++)
						t += -depvector[j];

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

	void print() {

		std::cout << "(";
		for (int i = 0; i < depvector.size() - 1; i++) {

			std::cout << depvector[i] << ",";

		}

		std::cout << depvector[depvector.size() - 1] << ")";

	}

	void printOrtho() {

		OrothognalVector();

		std::cout << "(";
		for (int i = 0; i < orthovector.size() - 1; i++) {

			std::cout << orthovector[i] << ",";

		}

		std::cout << orthovector[orthovector.size() - 1] << ")";

	}

	float dotProduct(std::vector<int> v, float mod) {

		if (v.size() != depvector.size()) {

			return -10000;

		} else {

			int dotprd = 0;
			for (int i = 0; i < v.size(); i++) {

				dotprd += v[i] * depvector[i];

			}

			return dotprd / mod;

		}

	}

	float NormalEucldianDistanace() {

		float distance = 0.0;

		for (int i = 0; i < orthovector.size(); i++) {

			distance += pow(orthovector[i], 2);

		}

		eculd = sqrt(distance);
		return eculd;

	}

};


#endif
