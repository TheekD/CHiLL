/*****************************************************************************
 Copyright (C) 2008 University of Southern California
 Copyright (C) 2009-2010 University of Utah
 All Rights Reserved.

 Purpose:
 generate suif code for omega

 Notes:

 History:
 02/01/06 created by Chun Chen
 *****************************************************************************/

#include <stack>
#include <code_gen/CG_roseBuilder.h>
#include <string>

struct ir_error: public std::runtime_error {
	ir_error(const std::string &msg) :
			std::runtime_error(msg) {
	}
};

using namespace SageBuilder;
using namespace SageInterface;
using namespace OmpSupport;

namespace omega {

//-----------------------------------------------------------------------------
// make suif initilization happy
//-----------------------------------------------------------------------------
char *k_ocg_comment;

// void __attribute__ ((constructor)) my_init(void) {
//   ANNOTE(k_ocg_comment, "omega_comment", TRUE);
// }

/*
 const char *libcode_gen_ver_string = "";
 const char *libcode_gen_who_string = "";
 const char *libcode_gen_suif_string = "";

 void init_code_gen(int&, char* []) {
 ANNOTE(k_ocg_comment, "omega_comment", TRUE);
 }

 void exit_code_gen(void) {
 }
 */
CG_roseBuilder::CG_roseBuilder(int is_fortran, SgGlobal* global, SgGlobal* firstScope,
		SgSymbolTable* symtab, SgSymbolTable* symtab2, SgNode* root) :
		isFortran(is_fortran), global_(global), global_scope(firstScope), symtab_(symtab), symtab2_(
				symtab2), root_(root) {
}


CG_roseBuilder::~CG_roseBuilder() {
}

// Manu:: returns true if input is in fortran, else returns false
bool CG_roseBuilder::isInputFortran() const{
	if (isFortran)
		return true;
	else
		return false;
}

//-----------------------------------------------------------------------------
// place holder generation
//-----------------------------------------------------------------------------
CG_outputRepr* CG_roseBuilder::CreateSubstitutedStmt(int, CG_outputRepr *stmt,
		const std::vector<std::string> &vars, std::vector<CG_outputRepr*> &subs) const {

	SgStatementPtrList* list = static_cast<CG_roseRepr *>(stmt)->list_;
	SgNode *tnl;
	SgStatement* statement;
	if (list != NULL) {
		//statement  = *((*list).begin());
		//tnl = isSgNode(statement);
		delete stmt;
		for (int i = 0; i < subs.size(); i++) {
                  if (subs[i] == NULL)
                        continue;

			CG_roseRepr *repr = static_cast<CG_roseRepr*>(subs[i]);
			SgExpression* op = repr->op_;

			for (SgStatementPtrList::iterator it = (*list).begin();
					it != (*list).end(); it++) {
				statement = (*it);
				tnl = isSgNode(statement);

				//    std::string master = tnl->unparseToString();

				int j;
				int not_in_symtab_;

				not_in_symtab_ = 0;

				SgVariableSymbol *vs = symtab_->find_variable(
						SgName(vars[i].c_str()));

				if (vs == NULL) {

					not_in_symtab_ = 1;

					vs = symtab2_->find_variable(SgName(vars[i].c_str()));
				}
				if (vs != NULL) {
					//std::string x =  vars[i].c_str() ;
					//std::string y =  isSgNode(op)->unparseToString();

					std::vector<SgVarRefExp *> array = substitute(tnl,
							(const SgVariableSymbol*) vs, op, root_);
					for (std::vector<SgVarRefExp *>::iterator it =
							array.begin(); it != array.end(); it++) {

						// std::string z = isSgNode(array[j])->unparseToString();
						if (isSgVarRefExp(op)) {
							if (strcmp(
									isSgVarRefExp(op)->get_symbol()->get_name().getString().c_str(),
									vs->get_name().getString().c_str())) {

								(*it)->set_symbol(
										isSgVarRefExp(op)->get_symbol());
								//   std::string z = isSgNode(array[j])->unparseToString();

								// isSgBinaryOp(array[j]->get_parent())->replace_expression(array[j], op);

							}
						} else if (isSgExpression(op)) {

							if (isSgBinaryOp((*it)->get_parent()))
								isSgBinaryOp((*it)->get_parent())->replace_expression(
										*it, op);
							else if (isSgUnaryOp((*it)->get_parent()))
								isSgUnaryOp((*it)->get_parent())->replace_expression(
										*it, op);
							else if (isSgExprListExp((*it)->get_parent()))
								isSgExprListExp((*it)->get_parent())->replace_expression(
										*it, op);
							else
								throw ir_error("unrecognized expression type");
						}

					}
					/* std::vector<SgVarRefExp *> array2 = substitute (tnl,(const SgVariableSymbol*) vs, op, root_);
					 if(array2.size() != 0)
					 throw ir_error("variable replacement unsuccessful");
					 */
				}

			}

			delete repr;
			subs[i] = NULL;

			if (subs[i] != NULL)
				throw ir_error("not freed properly");

		}

		return new CG_roseRepr(list);

	} else {
		tnl = static_cast<CG_roseRepr *>(stmt)->tnl_;
		//std::string master = tnl->unparseToString();

		if (tnl == NULL)
			throw ir_error("both list and tnl are null!!");

		delete stmt;
		int j;
		int not_in_symtab_;
	 for (int i = 0; i < subs.size(); i++) {
                if (subs[i] == NULL)
                       continue;
			not_in_symtab_ = 0;

			
			CG_roseRepr *repr = static_cast<CG_roseRepr*>(subs[i]);
			SgExpression* op = repr->op_;
			delete repr;
			subs[i] = NULL;

			SgVariableSymbol *vs = symtab_->find_variable(
					SgName(vars[i].c_str()));

			if (vs == NULL) {

				not_in_symtab_ = 1;

				vs = symtab2_->find_variable(SgName(vars[i].c_str()));
			}
			if (vs != NULL) {
				//std::string x =  vars[i].c_str() ;
				//std::string y =  isSgNode(op)->unparseToString();
				std::vector<SgVarRefExp *> array = substitute(tnl, vs, op,
						root_);

				if (not_in_symtab_ && isSgVarRefExp(op)) {
					if (strcmp(
							isSgVarRefExp(op)->get_symbol()->get_name().getString().c_str(),
							vs->get_name().getString().c_str())) {
						//     symtab2_->remove(vs);
					}
				}
				/*   else if(not_in_symtab_ && isSgVarRefExp(isSgAddOp(op)->get_lhs_operand())){
				 if(strcmp(isSgVarRefExp(isSgAddOp(op)->get_lhs_operand())->get_symbol()->get_name().getString().c_str(),\
                     vs->get_name().getString().c_str())){  
				 symtab2_->remove(vs);
				 }
				 }*/
				//symtab2_->remove(vs);
				for (std::vector<SgVarRefExp *>::iterator j = array.begin();
						j != array.end(); j++) {
					//   std::string z = isSgNode(array[j])->unparseToString();

					if (isSgVarRefExp(op)) {
						if (strcmp(
								isSgVarRefExp(op)->get_symbol()->get_name().getString().c_str(),
								vs->get_name().getString().c_str())) {
							(*j)->set_symbol(isSgVarRefExp(op)->get_symbol());
							//isSgBinaryOp(array[j]->get_parent())->replace_expression(array[j], op);
							//     std::string z = isSgNode(array[j])->unparseToString();

						}
					} else if (isSgExpression(op)) {

						if (isSgBinaryOp((*j)->get_parent()))
							isSgBinaryOp((*j)->get_parent())->replace_expression(
									*j, op);
						else if (isSgUnaryOp((*j)->get_parent()))
							isSgUnaryOp((*j)->get_parent())->replace_expression(
									*j, op);
						else if (isSgExprListExp((*j)->get_parent())) { // Manu:: fortran indices are stored this way
							isSgExprListExp((*j)->get_parent())->replace_expression(*j, op);
						}
						else
							throw ir_error("unrecognized expression type");
						/*   if(strcmp(isSgVarRefExp(isSgAddOp(op)->get_lhs_operand())->get_symbol()->get_name().getString().c_str(),\
                     vs->get_name().getString().c_str() )){
						 array[j]->set_symbol(isSgVarRefExp(isSgAddOp(op)->get_lhs_operand())->get_symbol());

						 */

					}

				}
				/*      std::vector<SgVarRefExp *> array2 = substitute (tnl,(const SgVariableSymbol*) vs, op, root_);
				 if(array2.size() != 0)
				 throw ir_error("variable replacement unsuccessful");
				 */
			}
			/*    SgExpression* exp = NULL;

			 if(stmt1 = isSgStatement(tnl)){
			 if (SgExprStatement* expr_stmt = isSgExprStatement(stmt1))
			 exp = expr_stmt->get_expression();
			 else if( block = isSgBasicBlock(tnl)){
			 SgStatementPtrList& stmts = block->get_statements();
			 SgExpression* exp2;
			 for(int i =0; i < stmts.size(); i++){
			 if(isSgExprStatement(stmts[i])){
			 exp2 = isSgExprStatement(stmts[i])->get_expression();
			 if(exp2 != NULL){

			 if(isSgBinaryOp(exp2)) {
			 substitute(isSgBinaryOp(exp2)->get_lhs_operand(), vs, op, root_, exp2);
			 substitute(isSgBinaryOp(exp2)->get_rhs_operand(), vs, op, root_, exp2);
			 }
			 else if (isSgUnaryOp(exp2))
			 substitute(isSgUnaryOp(exp2)->get_operand(), vs, op, root_, exp2);


			 }//end if

			 }//end   if
			 }//end for

			 }//end else
			 else if(SgForStatement* for_stmt = isSgForStatement(tnl)){
			 SgForStatement* temp = for_stmt;
			 while(isSgForStatement(temp)){



			 }




			 }


			 }//end if
			 else
			 exp = isSgExpression(tnl);

			 if(exp != NULL){
			 if(isSgBinaryOp(exp)) {
			 substitute(isSgBinaryOp(exp)->get_lhs_operand(), vs, op, root_, exp);
			 substitute(isSgBinaryOp(exp)->get_rhs_operand(), vs, op, root_, exp);
			 }
			 else if (isSgUnaryOp(exp))
			 substitute(isSgUnaryOp(exp)->get_operand(), vs, op, root_, exp);

			 }
			 // if (op.is_instr())
			 //   delete op.instr();
			 }
			 */
		}
		return new CG_roseRepr(tnl);
	}

}

//-----------------------------------------------------------------------------
// assignment generation
//-----------------------------------------------------------------------------
CG_outputRepr* CG_roseBuilder::CreateAssignment(int, CG_outputRepr *lhs,
		CG_outputRepr *rhs) const {
	if (lhs == NULL || rhs == NULL) {
		fprintf(stderr, "Code generation: Missing lhs or rhs\n");
		return NULL;
	}

	SgExpression* src = static_cast<CG_roseRepr*>(rhs)->op_;
	SgExpression* dst = static_cast<CG_roseRepr*>(lhs)->op_;

	SgExprStatement* ins = buildAssignStatement(dst, src);
	src->set_parent(ins);
	dst->set_parent(ins);

	SgStatementPtrList* new_list = new SgStatementPtrList;

	(*new_list).push_back(isSgStatement(ins));

	delete lhs;
	delete rhs;

	return new CG_roseRepr(new_list);

}

//-----------------------------------------------------------------------------
// function invocation generation
//-----------------------------------------------------------------------------
CG_outputRepr* CG_roseBuilder::CreateInvoke(const std::string &fname,
		std::vector<CG_outputRepr *> &list) const {

	// Manu:: debug
//	std::cout << "--------- CreateInvoke --------- \n";

	if (fname == std::string("max") || fname == std::string("min")) {
		if (list.size() == 0) {
			return NULL;
		} else if (list.size() == 1) {
			 return list[0];
		} else {
			 int last = list.size() - 1;
			SgExpression* op2 = static_cast<CG_roseRepr*>(list[last])->op_;
			delete list[last];
		    list.erase(list.end()-1);
			CG_roseRepr *repr = static_cast<CG_roseRepr*>(CreateInvoke(fname,
					list));
			SgExpression* op1 = repr->op_;


			SgExpression *ins;
			SgExprListExp* arg_list = buildExprListExp();
			appendExpression(arg_list, op1);
			appendExpression(arg_list, op2);
			SgVarRefExp* opaque_var;


			if (fname == std::string("max")) {
				opaque_var = buildOpaqueVarRefExp("__rose_gt", global_);
				ins = isSgExpression(buildFunctionCallExp(opaque_var, arg_list));

				// Manu:: fortran support
				if (isInputFortran()) {
					SgName fName("merge");
					SgTypeInt *retType = buildIntType();

					SgExpression *cond = static_cast<CG_roseRepr *>(CreateLE(new CG_roseRepr(op2), new CG_roseRepr(op1)))->op_;
		            appendExpression(arg_list, cond);
					ins = isSgExpression(buildFunctionCallExp(fName, retType, arg_list, global_));
//					std::cout << "--------- CreateInvoke:: " << isSgNode(ins)->unparseToString().c_str() << "\n";
				}

			} else {
				opaque_var = buildOpaqueVarRefExp("__rose_lt", global_);
				ins = isSgExpression(buildFunctionCallExp(opaque_var, arg_list));

				// Manu:: fortran support
				if (isInputFortran()) {
					SgName fName("merge");
					SgTypeInt *retType = buildIntType();

					SgExpression *cond = static_cast<CG_roseRepr *>(CreateLE(new CG_roseRepr(op1), new CG_roseRepr(op2)))->op_;
		            appendExpression(arg_list, cond);
					ins = isSgExpression(buildFunctionCallExp(fName, retType, arg_list, global_));
//					std::cout << "--------- CreateInvoke:: " << isSgNode(ins)->unparseToString().c_str() << "\n";
				}

			}

			repr->op_ = ins;
			return repr;
		}
	} else {
		fprintf(stderr,
				"Code generation: invoke function io_call not implemented\n");
		return NULL;
	}

}

//-----------------------------------------------------------------------------
// comment generation
//-----------------------------------------------------------------------------
CG_outputRepr* CG_roseBuilder::CreateComment(int,
		const std::string &commentText) const {
	if (commentText == std::string("")) {
		return NULL;
	}

	SgLocatedNode *tnl = new SgLocatedNode();
	buildComment(tnl, "//omega_comment: " + commentText);

	return new CG_roseRepr(isSgNode(tnl));

}

//-----------------------------------------------------------------------------
// if stmt gen operations
//-----------------------------------------------------------------------------
CG_outputRepr* CG_roseBuilder::CreateIf(int, CG_outputRepr *guardList,
		CG_outputRepr *true_stmtList, CG_outputRepr *false_stmtList) const {

	// static int if_counter = 1;
	// std::string s = std::string("omegaif_")+to_string(if_counter++);
	//  SgLabelStatement* label =buildLabelStatement(SgName(const_cast<char *>(s.c_str())));

	if (true_stmtList == NULL && false_stmtList == NULL) {
		delete guardList;
		return NULL;
	} else if (guardList == NULL) {
		return StmtListAppend(true_stmtList, false_stmtList);
	}

	SgExpression* header = static_cast<CG_roseRepr*>(guardList)->op_;

	SgStatementPtrList *then_part1, *else_part1;
	SgStatement* then_part;
	SgStatement* else_part;
	SgBasicBlock* then_part2;
	SgBasicBlock* else_part2;
	if (true_stmtList != NULL) {
		then_part1 = static_cast<CG_roseRepr*>(true_stmtList)->list_;
		if (then_part1 != NULL) {
			then_part = *((*then_part1).begin());

			if ((*then_part1).size() > 1) {
				then_part2 = buildBasicBlock();
				for (SgStatementPtrList::iterator it = (*then_part1).begin();
						it != (*then_part1).end(); it++) {
					then_part2->append_statement(*it);

				}
				then_part = isSgStatement(then_part2);

			}
		} else {
			// Manu:: fortran support (if part)
			if (isInputFortran()) {
				then_part2 = buildBasicBlock();
				then_part2->append_statement(isSgStatement(static_cast<CG_roseRepr*>(true_stmtList)->tnl_));
				then_part = isSgStatement(then_part2);
			} else
				then_part = isSgStatement(static_cast<CG_roseRepr*>(true_stmtList)->tnl_);
		}
	} else {
		then_part = NULL;
	}
	if (false_stmtList != NULL) {
		else_part1 = static_cast<CG_roseRepr*>(false_stmtList)->list_;
		if (else_part1 != NULL) {
			else_part = *((*else_part1).begin());
			if ((*else_part1).size() > 1) {
				else_part2 = buildBasicBlock();
				for (SgStatementPtrList::iterator it2 = (*else_part1).begin();
						it2 != (*else_part1).end(); it2++) {
					else_part2->append_statement(*it2);

				}
				else_part = isSgStatement(else_part2);

			}
		} else {
			// Manu:: fortran support (if part)
			if (isInputFortran()) {
				else_part2 = buildBasicBlock();
				else_part2->append_statement(isSgStatement(static_cast<CG_roseRepr*>(false_stmtList)->tnl_));
				else_part = isSgStatement(else_part2);
			} else
				else_part = isSgStatement(static_cast<CG_roseRepr*>(false_stmtList)->tnl_);
		}
	} else {
		else_part = NULL;
	}

	SgIfStmt* ti = buildIfStmt(header, isSgStatement(then_part),
			isSgStatement(else_part));

//  label->set_scope(ti);//may have to be shifted to after symbol table insertion
//  SgLabelSymbol* if_label = isSgLabelSymbol(label->get_symbol_from_symbol_table());

//  symtab_->insert( SgName(const_cast<char *>(s.c_str()))    ,  isSgSymbol(if_label));

	delete guardList;
	delete true_stmtList;
	delete false_stmtList;

	return new CG_roseRepr(isSgNode(ti));

}

//-----------------------------------------------------------------------------
// inductive variable generation, to be used in CreateLoop as control
//-----------------------------------------------------------------------------
CG_outputRepr* CG_roseBuilder::CreateInductive(CG_outputRepr *index,
		CG_outputRepr *lower, CG_outputRepr *upper, CG_outputRepr *step) const {

	if (index == NULL || lower == NULL || upper == NULL) {
		fprintf(stderr,
				"Code generation: something wrong in CreateInductive\n");
		return NULL;
	}

	if (step == NULL)
		step = new CG_roseRepr(isSgExpression(buildIntVal(1)));

	SgVarRefExp *index_sym = isSgVarRefExp(
			static_cast<CG_roseRepr*>(index)->op_);
	SgExpression* lower_bound = static_cast<CG_roseRepr*>(lower)->op_;
	SgExpression* upper_bound = static_cast<CG_roseRepr*>(upper)->op_;
	SgExpression* step_size = static_cast<CG_roseRepr*>(step)->op_;

	/*  label_sym *contLabel = new label_sym("");
	 label_sym *brkLabel = new label_sym("");  may not be required on rose?!
	 */

	SgStatement* for_init_stmt = buildAssignStatement(index_sym, lower_bound);
	SgLessOrEqualOp* cond = buildLessOrEqualOp(index_sym, upper_bound);
	SgExprStatement* test = buildExprStatement(cond);
	SgPlusAssignOp* increment = buildPlusAssignOp(index_sym, step_size);
	SgForStatement *for_stmt = buildForStatement(for_init_stmt,
			isSgStatement(test), increment, NULL);

	delete index;
	delete lower;
	delete upper;
	delete step;


	// Manu
	if (isInputFortran()) {
	//	std::cout << "CG_roseBuilder:: need to construct a fortran do statement\n";
        SgFortranDo * forStmt=new SgFortranDo(Sg_File_Info::generateDefaultFileInfoForTransformationNode());
        forStmt->set_has_end_statement(true);
        forStmt->set_bound(upper_bound);
        forStmt->set_increment(step_size);
        forStmt->set_initialization(isSgExprStatement(for_init_stmt)->get_expression());
        return new CG_roseRepr(isSgNode(forStmt));
	} else {
//		std::cout << "CG_roseBuilder:: for statement is fine\n";

		return new CG_roseRepr(isSgNode(for_stmt));

	}

}

//-----------------------------------------------------------------------------
// Attribute Creation
//-----------------------------------------------------------------------------
CG_outputRepr* CG_roseBuilder::CreateAttribute(CG_outputRepr *control,
		const std::string &commentText) const {

	SgNode *tnl = static_cast<CG_roseRepr*>(control)->tnl_;

	tnl->setAttribute("omega_comment", new AstTextAttribute(commentText));

	return static_cast<CG_roseRepr*>(control);

}

//-----------------------------------------------------------------------------
// Pragma Attribute
//-----------------------------------------------------------------------------
CG_outputRepr* CG_roseBuilder::CreatePragmaAttribute(CG_outputRepr *stmt, int looplevel, const std::string &pragmaText) const {
	SgNode *tnl = static_cast<CG_roseRepr*>(stmt)->tnl_;
	CodeInsertionAttribute* attr = NULL;
	if (!tnl->attributeExists("code_insertion")) {
		attr = new CodeInsertionAttribute();
		tnl->setAttribute("code_insertion", attr);
	}
	else {
		attr = static_cast<CodeInsertionAttribute*>(tnl->getAttribute("code_insertion"));
	}
	attr->add(new PragmaInsertion(looplevel, pragmaText));
	return stmt;
}

//-----------------------------------------------------------------------------
// Prefetch Attribute
//-----------------------------------------------------------------------------
CG_outputRepr* CG_roseBuilder::CreatePrefetchAttribute(CG_outputRepr* stmt, int looplevel, const std::string &arrName, int hint) const {
	SgNode *tnl = static_cast<CG_roseRepr*>(stmt)->tnl_;
	CodeInsertionAttribute *attr = getOrCreateCodeInsertionAttribute(tnl);
	attr->add(new MMPrefetchInsertion(looplevel, arrName, hint));
}

//-----------------------------------------------------------------------------
// loop stmt generation
//-----------------------------------------------------------------------------
CG_outputRepr* CG_roseBuilder::CreateLoop(int, CG_outputRepr *control,
		CG_outputRepr *stmtList) const {
	if (stmtList == NULL) {
		delete control;
		return NULL;
	} else if (control == NULL) {
		fprintf(stderr, "Code generation: no inductive for this loop\n");
		return stmtList;
	}

	SgNode *tnl = static_cast<CG_roseRepr*>(control)->tnl_;
	SgForStatement *tf = isSgForStatement(tnl);

	// Manu :: fortran support
	SgFortranDo *tfd = NULL;
	if (isInputFortran()) {
		tfd = isSgFortranDo(tnl);
	}
	// Manu:: debug
/*	if (!tf) {
		std::cout << "CreateLoop:: Not a for loop\n";
		if (isSgFortranDo(tnl))
			std::cout << "CreateLoop:: It is a fortran do loop\n";
	}
*/

	SgStatementPtrList * body = static_cast<CG_roseRepr*>(stmtList)->list_;

	if (body != NULL) {
		if (!((*body).empty())) {
			if ((*body).size() == 1) {
				// if(isSgBasicBlock(*((*body).begin()))){
				if (!isInputFortran()) {  // Manu:: added if-else for fortran support
				  tf->set_loop_body(*((*body).begin()));
				  (*((*body).begin()))->set_parent(tf);
				} else {
					SgBasicBlock* bb1 = buildBasicBlock();
					bb1->set_parent(tfd);
					bb1->append_statement(*((*body).begin()));
					tfd->set_body(bb1);
				}
				//  }
				/*    else{
				 SgBasicBlock* bb1 = buildBasicBlock();
				 bb1->set_parent(tf);
				 bb1->append_statement(*((*body).begin()));
				 tf->set_loop_body(bb1);

				 }*/
			} else {
				// Manu:: support for fortran label (do - continue)
				SgName *sname = NULL;

				SgBasicBlock* bb = buildBasicBlock();
				if (!isInputFortran())
				    bb->set_parent(tf);
				else
					bb->set_parent(tfd);
				for (SgStatementPtrList::iterator it = (*body).begin();
						it != (*body).end(); it++) {
					bb->append_statement(*it);
					(*it)->set_parent(bb);
				}
				if (!isInputFortran())
				   tf->set_loop_body(bb);
				else {
					tfd->set_body(bb);
				}
			}
		}
	} else {
		SgNode* tnl2 = static_cast<CG_roseRepr*>(stmtList)->tnl_;

		if (tnl2 != NULL) {
			if (!isInputFortran()) {
			   tf->set_loop_body(isSgStatement(tnl2));
			   tnl2->set_parent(tf);
			} else {
				SgBasicBlock* bb1 = buildBasicBlock();
				bb1->set_parent(tfd);
				bb1->append_statement(isSgStatement(tnl2));
				tfd->set_body(bb1);
  			    tnl2->set_parent(bb1);
			}
		}
	}

	delete stmtList;

	return control;
}

//-----------------------------------------------------------------------------
// basic int, identifier gen operations
//-----------------------------------------------------------------------------
CG_outputRepr* CG_roseBuilder::CreateInt(int _i) const {
	return new CG_roseRepr(isSgExpression(buildIntVal(_i)));
}
bool CG_roseBuilder::isInteger(CG_outputRepr *op) const{

	 SgExpression *op1 = static_cast<CG_roseRepr *>(op)->op_;

	 if(op1)
       if(isSgIntVal(op1))
	       return true;

     return false;
}
CG_outputRepr* CG_roseBuilder::CreateIdent(const std::string &_s) const {

	SgVariableSymbol *vs = symtab_->find_variable(SgName(_s.c_str()));
	SgVariableSymbol *vs2 = symtab2_->find_variable(SgName(_s.c_str()));

	if (vs == NULL && vs2 == NULL) {

		SgVariableDeclaration* defn = buildVariableDeclaration(
				SgName(_s.c_str()), buildIntType());
		SgInitializedNamePtrList& variables = defn->get_variables();
		SgInitializedNamePtrList::const_iterator i = variables.begin();
		SgInitializedName* initializedName = *i;
		vs = new SgVariableSymbol(initializedName);
		prependStatement(defn, isSgScopeStatement(root_));

		vs->set_parent(symtab2_);
		symtab2_->insert(SgName(_s.c_str()), vs);
		return new CG_roseRepr(isSgExpression(buildVarRefExp(vs)));

	}

	/* May have problem */

	if (!isSgExpression(buildVarRefExp(SgName(_s.c_str()))))
		throw ir_error("error in Create ident!!");
	if (vs2 != NULL)
		return new CG_roseRepr(isSgExpression(buildVarRefExp(vs2)));

	return new CG_roseRepr(isSgExpression(buildVarRefExp(vs)));

}

//-----------------------------------------------------------------------------
// binary arithmetic operations
//-----------------------------------------------------------------------------
CG_outputRepr* CG_roseBuilder::CreatePlus(CG_outputRepr *lop,
		CG_outputRepr *rop) const {
	if (rop == NULL) {
		return lop;
	} else if (lop == NULL) {
		return rop;
	}

	SgExpression* op1 = static_cast<CG_roseRepr*>(lop)->op_;
	SgExpression* op2 = static_cast<CG_roseRepr*>(rop)->op_;

	SgAddOp *ins = buildAddOp(op1, op2);
	op1->set_parent(ins);
	op2->set_parent(ins);
	delete lop;
	delete rop;

	return new CG_roseRepr(isSgExpression(ins));

}

CG_outputRepr* CG_roseBuilder::CreateMinus(CG_outputRepr *lop,
		CG_outputRepr *rop) const {
	if (rop == NULL) {
		return lop; /* May Cause Problem */
	} else if (lop == NULL) {
		SgExpression *op = static_cast<CG_roseRepr*>(rop)->op_;
		SgMinusOp *ins = buildMinusOp(op);

		delete rop;

		return new CG_roseRepr(isSgExpression(ins));
	} else {
		SgExpression* op1 = static_cast<CG_roseRepr*>(lop)->op_;
		SgExpression* op2 = static_cast<CG_roseRepr*>(rop)->op_;

		SgSubtractOp *ins = buildSubtractOp(op1, op2);
		op1->set_parent(ins);
		op2->set_parent(ins);
		delete lop;
		delete rop;
		return new CG_roseRepr(isSgExpression(ins));
	}

}

CG_outputRepr* CG_roseBuilder::CreateTimes(CG_outputRepr *lop,
		CG_outputRepr *rop) const {
	if (rop == NULL || lop == NULL) {
		if (rop != NULL) {
			rop->clear();
			delete rop;
		}
		if (lop != NULL) {
			lop->clear();
			delete lop;
		}
		return NULL;
	}

	SgExpression* op1 = static_cast<CG_roseRepr*>(lop)->op_;
	SgExpression* op2 = static_cast<CG_roseRepr*>(rop)->op_;

	SgMultiplyOp *ins = buildMultiplyOp(op1, op2);
	op1->set_parent(ins);
	op2->set_parent(ins);
	delete lop;
	delete rop;

	return new CG_roseRepr(isSgExpression(ins));

}

CG_outputRepr* CG_roseBuilder::CreateIntegerFloor(CG_outputRepr *lop,
		CG_outputRepr *rop) const {
	if (rop == NULL) {
		fprintf(stderr, "Code generation: divide by NULL\n");
		return NULL;
	} else if (lop == NULL) {
		delete rop;
		return NULL;
	}

	//  (6+5)*10 / 4
	SgExpression* op1 = static_cast<CG_roseRepr*>(lop)->op_;
	SgExpression* op2 = static_cast<CG_roseRepr*>(rop)->op_;

	// bugs in SUIF prevent use of correct io_divfloor
	SgDivideOp *ins = buildDivideOp(op1, op2);

	delete lop;
	delete rop;

	return new CG_roseRepr(isSgExpression(ins));

}

CG_outputRepr* CG_roseBuilder::CreateIntegerMod(CG_outputRepr *lop,
		CG_outputRepr *rop) const {
	if (rop == NULL || lop == NULL) {
		return NULL;
	}

	SgExpression* op1 = static_cast<CG_roseRepr*>(lop)->op_;
	SgExpression* op2 = static_cast<CG_roseRepr*>(rop)->op_;

	// bugs in SUIF prevent use of correct io_mod
	SgModOp *ins;
	if (!isInputFortran()) {
		ins = buildModOp(op1, op2);
		delete lop;
		delete rop;

		return new CG_roseRepr(isSgExpression(ins));
	} else { // Manu:: fortran mod is a function call and not an operator (f77 and f90)
		SgExpression *fins;
		SgName fName("MOD");
		SgExprListExp* arg_list = buildExprListExp();
		appendExpression(arg_list, op1);
		appendExpression(arg_list, op2);
		SgTypeInt *retType = buildIntType();
		fins = isSgExpression(buildFunctionCallExp(fName, retType, arg_list, global_));
		return new CG_roseRepr(isSgExpression(fins));
	}

}

//-----------------------------------------------------------------------------
// binary logical operations
//-----------------------------------------------------------------------------
CG_outputRepr* CG_roseBuilder::CreateAnd(CG_outputRepr *lop,
		CG_outputRepr *rop) const {
	/*if (rop == NULL || lop == NULL) {
		return NULL;
	}*/

	if (rop == NULL)
		return lop;
	else if (lop == NULL)
		return rop;

	SgExpression* op1 = static_cast<CG_roseRepr*>(lop)->op_;
	SgExpression* op2 = static_cast<CG_roseRepr*>(rop)->op_;

	SgAndOp *ins = buildAndOp(op1, op2);

	delete lop;
	delete rop;

	return new CG_roseRepr(isSgExpression(ins));

}

//-----------------------------------------------------------------------------
// binary relational operations
//-----------------------------------------------------------------------------
/*CG_outputRepr* CG_roseBuilder::CreateGE(CG_outputRepr *lop,
		CG_outputRepr *rop) const {
	return CreateLE(rop, lop);
}*/

CG_outputRepr* CG_roseBuilder::CreateLE(CG_outputRepr *lop,
		CG_outputRepr *rop) const {
	if (rop == NULL || lop == NULL) {
		return NULL;
	}

	SgExpression* op1 = static_cast<CG_roseRepr*>(lop)->op_;
	SgExpression* op2 = static_cast<CG_roseRepr*>(rop)->op_;

	SgLessOrEqualOp *ins = buildLessOrEqualOp(op1, op2);

	delete lop;
	delete rop;

	return new CG_roseRepr(isSgExpression(ins));

}

CG_outputRepr* CG_roseBuilder::CreateEQ(CG_outputRepr *lop,
		CG_outputRepr *rop) const {
	if (rop == NULL || lop == NULL) {
		return NULL;
	}

	SgExpression* op1 = static_cast<CG_roseRepr*>(lop)->op_;
	SgExpression* op2 = static_cast<CG_roseRepr*>(rop)->op_;

	SgEqualityOp *ins = buildEqualityOp(op1, op2);

	delete lop;
	delete rop;

	return new CG_roseRepr(isSgExpression(ins));

}

//-----------------------------------------------------------------------------
// stmt list gen operations
//-----------------------------------------------------------------------------
/*CG_outputRepr* CG_roseBuilder::CreateStmtList(CG_outputRepr *singleton) const {

	if (singleton == NULL) {
		return new CG_roseRepr(new SgStatementPtrList);
	}

	SgStatementPtrList *tnl = static_cast<CG_roseRepr *>(singleton)->list_;
	SgNode* sgn = static_cast<CG_roseRepr *>(singleton)->tnl_;

	if (tnl == NULL)
		tnl = new SgStatementPtrList;

	if (sgn == NULL) {
		SgExpression* op = static_cast<CG_roseRepr *>(singleton)->op_;

		if (op != NULL)
			(*tnl).push_back(
					buildExprStatement(
							static_cast<CG_roseRepr *>(singleton)->op_));

	} else
		(*tnl).push_back(isSgStatement(sgn));

	delete singleton;
	return new CG_roseRepr(tnl);

//    tnl = isSgNode(buildBasicBlock(buildExprStatement(static_cast<CG_roseRepr *>(singleton)->op_)));

//  delete singleton;
//  return new CG_roseRepr(tnl);

}

CG_outputRepr* CG_roseBuilder::StmtListInsertLast(CG_outputRepr *list,
		CG_outputRepr *node) const {
	return StmtListAppend(list, node);
}
*/
CG_outputRepr* CG_roseBuilder::StmtListAppend(CG_outputRepr *list1,
		CG_outputRepr *list2) const {

	if (list2 == NULL) {
		return list1;
	} else if (list1 == NULL) {
		return list2;
	}

	// SgStatement* parent;
	//   SgStatement* stmt1;
	//   SgStatement* stmt2;

	SgStatementPtrList* new_list;

	SgStatementPtrList* tnl1 = static_cast<CG_roseRepr *>(list1)->list_;
	SgStatementPtrList* tnl2 = static_cast<CG_roseRepr *>(list2)->list_;
	SgNode* one = static_cast<CG_roseRepr *>(list1)->tnl_;
	SgNode* two = static_cast<CG_roseRepr *>(list2)->tnl_;

	SgExpression* exp1 = static_cast<CG_roseRepr *>(list1)->op_;
	SgExpression* exp2 = static_cast<CG_roseRepr *>(list2)->op_;

	if (exp1 || exp2)
		throw ir_error("error in stmtlistappend!!");

	if (tnl1 && one)
		throw ir_error("error in stmtlistappend!!");

	if (tnl2 && two)
		throw ir_error("error in stmtlistappend!!");
//  SgNode* sg1 = static_cast<CG_roseRepr *>(list1)->tnl_;

//if((*tnl1).empty()){

//  if(SgStatement* stmt = isSgStatement(sg1))
// (*tnl1).push_back(stmt); 
//else if(isSgScopeStatement(sg1)){
//     SgStatementPtrList scopeStmtPtrLst = isSgScopeStatement(sg1)->generateStatementList();

//    for(SgStatementPtrList::iterator it1 = scopeStmtPtrLst.begin();it1 != scopeStmtPtrLst.end(); it1++)          
//        (*tnl1).push_back(*it1);
//}
//}

	if ((tnl1 == NULL) && (tnl2 == NULL)) {

		if ((one != NULL) && (two != NULL)) {

			new_list = new SgStatementPtrList;

			(*new_list).push_back(isSgStatement(one));
			(*new_list).push_back(isSgStatement(two));

			CG_roseRepr* new_rep = new CG_roseRepr(new_list);

			return static_cast<CG_outputRepr *>(new_rep);

		} else if ((one != NULL) && (two == NULL)) {

			return static_cast<CG_outputRepr *>(new CG_roseRepr(one));

		} else if ((two != NULL) && (one == NULL)) {
			return static_cast<CG_outputRepr *>(new CG_roseRepr(two));

		}

	} else {
		if ((tnl2 != NULL) && (tnl1 == NULL)) {
			/*  for(SgStatementPtrList::iterator it = (*tnl2).begin(); it != (*tnl2).end(); it++)
			 {
			 (*tnl1).push_back(*it);

			 }
			 */
			if (one == NULL)
				return list2;
			else {
				new_list = new SgStatementPtrList;
				(*new_list).push_back(isSgStatement(one));

				for (SgStatementPtrList::iterator it = (*tnl2).begin();
						it != (*tnl2).end(); it++) {
					(*new_list).push_back(*it);

				}
				//delete list2;
				return static_cast<CG_outputRepr *>(new CG_roseRepr(new_list));
			}
		} else if ((tnl1 != NULL) && (tnl2 == NULL)) {
			if (two == NULL)
				return list1;
			else {

				(*tnl1).push_back(isSgStatement(two));
				//  delete list1;
				return static_cast<CG_outputRepr *>(new CG_roseRepr(tnl1));

			}

		} else if ((tnl1 != NULL) && (tnl2 != NULL)) {

			for (SgStatementPtrList::iterator it = (*tnl2).begin();
					it != (*tnl2).end(); it++) {
				(*tnl1).push_back(*it);

			}

			// delete list2;
			// delete list1;
			return static_cast<CG_outputRepr *>(new CG_roseRepr(tnl1));
		}
//else{
//    SgNode* tnll2 =  static_cast<CG_roseRepr *>(list2)->tnl_;
//   if(tnll2 != NULL){
//     if(isSgStatement(tnll2)) 
//      (*tnl1).push_back(isSgStatement(tnll2)); 
//     else if(isSgScopeStatement(tnll2)){
//        SgStatementPtrList scopeStmtPtrLst1 = isSgScopeStatement(tnll2)->generateStatementList();

//        for(SgStatementPtrList::iterator it2 = scopeStmtPtrLst1.begin();it2 !=  scopeStmtPtrLst1.end(); it2++)          
//        (*tnl1).push_back(*it2);

//    }
//} 
//    else{ 
//    SgStatement*    stmt2 = isSgStatement(buildExprStatement(static_cast<CG_roseRepr *>(list2)->op_));
//   (*tnl1).push_back(stmt2);

//   }

//}
		//  stmt2 = isSgStatement(tnl2);

//   std::string c = tnl1->unparseToString();    

//   std::string d = isSgNode(stmt2)->unparseToString();    

//  if(isSgForStatement(tnl1) || isSgBasicBlock(tnl1))
//    isSgScopeStatement(tnl1)->append_statement(stmt2);
//  else
//  {
		//      stmt1  = isSgStatement(tnl1);
		// parent = isSgStatement(tnl1->get_parent());
		//  if(isSgForStatement(tnl1->get_parent()) || isSgBasicBlock(tnl1->get_parent()))
		//    isSgScopeStatement(tnl1->get_parent())->append_statement(stmt2);
		//  else if (isSgStatement(tnl1->get_parent()))
		//    isSgStatement(tnl1->get_parent())->insert_statement(stmt1, stmt2, false);

// } 

	}
//  delete list2;

//  return list1;

}


CG_outputRepr* CG_roseBuilder::CreateDim3(const char* varName, CG_outputRepr* arg1,
		CG_outputRepr* arg2, CG_outputRepr* arg3) const {

	//SgName type_name("dim3");
	//SgClassSymbol * type_symbol = global_scope->lookup_class_symbol(type_name);
	//	SgClassDeclaration * type_decl = isSgClassDeclaration(
	//		type_symbol->get_declaration());

	//SgVariableDeclaration * var_decl = buildVariableDeclaration(varName, type_symbol->get_type());

	SgFunctionSymbol * ctor_symbol = global_scope->lookup_function_symbol(
			SgName("dim3"));

	SgExprListExp * ctor_args;
	if(arg3 != NULL)
	ctor_args = buildExprListExp(static_cast<CG_roseRepr*>(arg1)->op_,
			static_cast<CG_roseRepr*>(arg2)->op_, static_cast<CG_roseRepr*>(arg3)->op_);
	else
    ctor_args = buildExprListExp(static_cast<CG_roseRepr*>(arg1)->op_,
    		static_cast<CG_roseRepr*>(arg2)->op_);
	SgFunctionCallExp * dim3_func_call = buildFunctionCallExp(
			buildFunctionRefExp(ctor_symbol->get_declaration()), ctor_args);

	char joined_str[20];

	strcpy(joined_str, "dim3 ");
	strcat(joined_str, varName);

	SgExprStatement* decl = buildAssignStatement(
			buildOpaqueVarRefExp(joined_str, isSgScopeStatement(root_)),
			dim3_func_call);

	SgStatementPtrList *tnl2 = new SgStatementPtrList;

	//   (*tnl2).push_back(var_decl);
	(*tnl2).push_back(decl);
	return new CG_roseRepr(tnl2);

}

/*CG_outputRepr* CG_roseBuilder::CreateDim3(const char* varName, int arg1,
		int arg2) const {

	SgName type_name("dim3");
	SgClassSymbol * type_symbol = global_scope->lookup_class_symbol(type_name);
	SgClassDeclaration * type_decl = isSgClassDeclaration(
			type_symbol->get_declaration());

	//SgVariableDeclaration * var_decl = buildVariableDeclaration(varName, type_symbol->get_type());

	SgFunctionSymbol * ctor_symbol = global_scope->lookup_function_symbol(
			SgName("dim3"));

	SgExprListExp * ctor_args = buildExprListExp(buildIntVal(arg1),
			buildIntVal(arg2));

	SgFunctionCallExp * dim3_func_call = buildFunctionCallExp(
			buildFunctionRefExp(ctor_symbol->get_declaration()), ctor_args);

	char joined_str[20];

	strcpy(joined_str, "dim3 ");
	strcat(joined_str, varName);

	SgExprStatement* decl = buildAssignStatement(
			buildOpaqueVarRefExp(joined_str, isSgScopeStatement(root_)),
			dim3_func_call);

	SgStatementPtrList *tnl2 = new SgStatementPtrList;

	//   (*tnl2).push_back(var_decl);
	(*tnl2).push_back(decl);
	return new CG_roseRepr(tnl2);
}

CG_outputRepr* CG_roseBuilder::CreateDim3(const char* varName, int arg1,
		int arg2, int arg3) const {

	SgName type_name("dim3");
	SgClassSymbol * type_symbol = global_scope->lookup_class_symbol(type_name);
	SgClassDeclaration * type_decl = isSgClassDeclaration(
			type_symbol->get_declaration());

	//SgVariableDeclaration * var_decl = buildVariableDeclaration(varName, type_symbol->get_type());

	SgFunctionSymbol * ctor_symbol = global_scope->lookup_function_symbol(
			SgName("dim3"));

	SgExprListExp * ctor_args = buildExprListExp(buildIntVal(arg1),
			buildIntVal(arg2), buildIntVal(arg3));

	SgFunctionCallExp * dim3_func_call = buildFunctionCallExp(
			buildFunctionRefExp(ctor_symbol->get_declaration()), ctor_args);

	char joined_str[20];

	strcpy(joined_str, "dim3 ");
	strcat(joined_str, varName);

	SgExprStatement* decl = buildAssignStatement(
			buildOpaqueVarRefExp(joined_str, isSgScopeStatement(root_)),
			dim3_func_call);

	SgStatementPtrList *tnl2 = new SgStatementPtrList;

	//   (*tnl2).push_back(var_decl);
	(*tnl2).push_back(decl);
	return new CG_roseRepr(tnl2);

	

}
*/

/*CG_outputRepr* CG_suifBuilder::CreateKernel(immed_list* iml) const {
 instruction *ins = new in_rrr(io_mrk);
 ins->append_annote(k_cuda_kernel, iml);
 tree_node_list *tnl = new tree_node_list;
 tnl->append(new tree_instr(ins));
 return new CG_suifRepr(tnl);
 }

 type_node* CG_suifBuilder::ModifyType(type_node* base, const char* modifier) const {
 modifier_type* result = new modifier_type(TYPE_NULL, base);
 immed_list *iml = new immed_list;
 iml->append(immed((char*)modifier));
 result->append_annote(k_cuda_modifier, iml);
 return result;
 }
 */

std::vector<SgVarRefExp *> substitute(SgNode *in, const SgVariableSymbol *sym,
		SgExpression* expr, SgNode* root) {

	SgStatement* stmt;
	SgExpression* op;
	std::vector<SgVarRefExp *> arrays;

	if (in != NULL) {
		if (stmt = isSgStatement(in)) {
			if (isSgBasicBlock(stmt)) {
				SgStatementPtrList& stmts =
						isSgBasicBlock(stmt)->get_statements();
				for (int i = 0; i < stmts.size(); i++) {
					stmts[i]->set_parent(stmt);
					std::vector<SgVarRefExp *> a = substitute(
							isSgNode(stmts[i]), sym, expr, root);
					std::copy(a.begin(), a.end(), back_inserter(arrays));
				}
			} else if (isSgForStatement(stmt)) {
				SgForStatement *tnf = isSgForStatement(stmt);
				tnf->get_for_init_stmt()->set_parent(tnf);
				tnf->get_test()->set_parent(tnf);
				tnf->get_increment()->set_parent(tnf);
				tnf->get_loop_body()->set_parent(tnf);
				std::vector<SgVarRefExp *> a = substitute(
						isSgNode(tnf->get_for_init_stmt()), sym, expr, root);
				std::copy(a.begin(), a.end(), back_inserter(arrays));
				std::vector<SgVarRefExp *> a1 = substitute(
						isSgNode(tnf->get_test()), sym, expr, root);
				std::copy(a1.begin(), a1.end(), back_inserter(arrays));
				std::vector<SgVarRefExp *> a2 = substitute(
						isSgNode(tnf->get_increment()), sym, expr, root);
				std::copy(a2.begin(), a2.end(), back_inserter(arrays));
				std::vector<SgVarRefExp *> a3 = substitute(
						isSgNode(tnf->get_loop_body()), sym, expr, root);
				std::copy(a3.begin(), a3.end(), back_inserter(arrays));
			} else if (isSgFortranDo(stmt)) { // Manu:: fortran support
				SgFortranDo *tnf = isSgFortranDo(stmt);
				tnf->get_initialization()->set_parent(tnf);
				tnf->get_bound()->set_parent(tnf);
				tnf->get_increment()->set_parent(tnf);
				tnf->get_body()->set_parent(tnf);
				std::vector<SgVarRefExp *> a = substitute(
						isSgNode(tnf->get_initialization()), sym, expr, root);
				std::copy(a.begin(), a.end(), back_inserter(arrays));
				std::vector<SgVarRefExp *> a1 = substitute(
						isSgNode(tnf->get_bound()), sym, expr, root);
				std::copy(a1.begin(), a1.end(), back_inserter(arrays));
				std::vector<SgVarRefExp *> a2 = substitute(
						isSgNode(tnf->get_increment()), sym, expr, root);
				std::copy(a2.begin(), a2.end(), back_inserter(arrays));
				std::vector<SgVarRefExp *> a3 = substitute(
						isSgNode(tnf->get_body()), sym, expr, root);
				std::copy(a3.begin(), a3.end(), back_inserter(arrays));
			} else if (isSgForInitStatement(stmt)) {

				SgStatementPtrList& stmts =
						isSgForInitStatement(stmt)->get_init_stmt();

				for (SgStatementPtrList::iterator it = stmts.begin();
						it != stmts.end(); it++) {
					std::vector<SgVarRefExp *> a = substitute(isSgNode(*it),
							sym, expr, root);

					std::copy(a.begin(), a.end(), back_inserter(arrays));
				}
			}
			/*else if(isSgFortranDo(stmt)){
			 SgFortranDo *tfortran =  isSgFortranDo(stmt);
			 omega::CG_roseRepr *r = new omega::CG_roseRepr(isSgStatement(tfortran->get_body()));
			 std::vector<IR_ArrayRef *> a = FindArrayRef(r);
			 delete r;
			 std::copy(a.begin(), a.end(), back_inserter(arrays));
			 }*/
			else if (isSgVariableDeclaration(stmt)) {
				if (SgExpression *init =
						isSgVariableDeclaration(stmt)->get_variables().front()->get_initializer()) {
					if (isSgAssignInitializer(init)) {
						std::vector<SgVarRefExp *> a = substitute(
								isSgAssignInitializer(init)->get_operand(), sym,
								expr, root);
						std::copy(a.begin(), a.end(), back_inserter(arrays));
					}
				}
			} else if (isSgIfStmt(stmt)) {
				SgIfStmt* tni = isSgIfStmt(stmt);
				//tni->get_conditional()->set_parent(tni);
				//tni->get_true_body()->set_parent(tni);
				//tni->get_false_body()->set_parent(tni);
				std::vector<SgVarRefExp *> a = substitute(
						isSgNode(tni->get_conditional()), sym, expr, root);
				std::copy(a.begin(), a.end(), back_inserter(arrays));
				std::vector<SgVarRefExp *> a1 = substitute(
						isSgNode(tni->get_true_body()), sym, expr, root);
				std::copy(a1.begin(), a1.end(), back_inserter(arrays));
				std::vector<SgVarRefExp *> a2 = substitute(
						isSgNode(tni->get_false_body()), sym, expr, root);
				std::copy(a2.begin(), a2.end(), back_inserter(arrays));
			} else if (isSgExprStatement(stmt)) {
				(isSgExprStatement(stmt)->get_expression())->set_parent(
						isSgExprStatement(stmt));
				std::vector<SgVarRefExp *> a = substitute(
						isSgNode(isSgExprStatement(stmt)->get_expression()),
						sym, expr, root);
				std::copy(a.begin(), a.end(), back_inserter(arrays));
			}    //end else if
		}    //end if
		else {
			op = isSgExpression(in);
			// std::string x = isSgNode(op)->unparseToString();
			std::string y = sym->get_name().getString();
//			std::cout << "------substitute else:: " <<  in->unparseToString().c_str() << ", " << y.c_str() << "\n";

			if (isSgBinaryOp(op)) {

				isSgBinaryOp(op)->get_lhs_operand()->set_parent(op);
				isSgBinaryOp(op)->get_rhs_operand()->set_parent(op);

				std::vector<SgVarRefExp *> a = substitute(
						isSgBinaryOp(op)->get_lhs_operand(), sym, expr, root);
				std::copy(a.begin(), a.end(), back_inserter(arrays));
				std::vector<SgVarRefExp *> a1 = substitute(
						isSgBinaryOp(op)->get_rhs_operand(), sym, expr, root);
				std::copy(a1.begin(), a1.end(), back_inserter(arrays));
			} else if (isSgUnaryOp(op)) {
				//isSgUnaryOp(op)->get_operand()->set_parent(op);
				//std::string x = isSgNode(op)->unparseToString();
				//std::cout<<x<<std::endl;
				std::vector<SgVarRefExp *> a = substitute(
						isSgUnaryOp(op)->get_operand(), sym, expr, root);
				std::copy(a.begin(), a.end(), back_inserter(arrays));
			} else if (isSgVarRefExp(op)) {
				std::string z =
						isSgVarRefExp(op)->get_symbol()->get_name().getString();
				if (!strcmp(z.c_str(), y.c_str())) {
					//isSgVarRefExp(op)->set_symbol(isSgVarRefExp(expr)->get_symbol());
					arrays.push_back(isSgVarRefExp(op));
					//replaceVariableReferences(root, isSgVarRefExp(in)->get_symbol(), temp);
					//r = true;
				}        //end if
			}        //end else if
			else if (isSgCallExpression(op)) {
				SgExprListExp* exprs = isSgCallExpression(op)->get_args();
				SgExpressionPtrList &expr_list = exprs->get_expressions();

				for (SgExpressionPtrList::iterator it = expr_list.begin();
						it != expr_list.end(); it++) {
					std::vector<SgVarRefExp *> a = substitute(isSgNode(*it),
							sym, expr, root);
					std::copy(a.begin(), a.end(), back_inserter(arrays));
				}
			} else if (isSgExprListExp(op)) { // Manu:: fortran indices are stored this way
				SgExpressionPtrList &expr_list = isSgExprListExp(op)->get_expressions();

				for (SgExpressionPtrList::iterator it = expr_list.begin();
						it != expr_list.end(); it++) {
					std::vector<SgVarRefExp *> a = substitute(isSgNode(*it),
							sym, expr, root);
					std::copy(a.begin(), a.end(), back_inserter(arrays));
				}

			}

			//end else if
			//else if(!isSgValueExp(op))
			//	throw ir_error("unrecognized expression type");
		}        //end else
	}        //end if

	/*  bool r = false;
	 if (isSgVarRefExp(in) && (isSgVarRefExp(in)->get_symbol()  == sym)) {
	 omega::CG_roseRepr *result = new omega::CG_roseRepr(expr);
	 SgExpression* expr1 =  result->GetExpression();
	 delete result;
	 SgVariableSymbol* temp = isSgVarRefExp(expr1)->get_symbol();
	 parent->replace_expression(in, expr1);
	 replaceVariableReferences(root, isSgVarRefExp(in)->get_symbol(), temp);
	 r = true;
	 }
	 else if(isSgBinaryOp(in)){
	 substitute(isSgBinaryOp(in)->get_lhs_operand(), sym, expr, root, in);
	 substitute(isSgBinaryOp(in)->get_rhs_operand(), sym, expr, root, in);
	 }
	 else if(isSgUnaryOp(in))
	 substitute(isSgUnaryOp(in)->get_operand(), sym, expr, root, in);

	 */

	return arrays;
}

/*bool substitute(SgStatement *tn, SgVariableSymbol *sym, SgExpression* expr, SgNode* root, SgSymbolTable* symtab) {
 if (tn == NULL)
 return false;

 bool r = false;
 if( tn != NULL){
 if(isSgExpression(tn)){
 r = substitute(isSgExpression(tn), sym, expr, root, isSgExpression(tn)) || r;

 }
 else {
 omega::CG_roseRepr *result = new omega::CG_roseRepr(expr);
 SgExpression* expr1 = result->GetExpression();
 tn->replace_expression(buildVarRefExp(sym), expr1);
 for (unsigned i = 0; i < tn->get_numberOfTraversalSuccessors(); i++)
 r = substitute(isSgStatement(tn->get_traversalSuccessorByIndex(i)), sym, expr, root, symtab) || r;

 }
 }
 return r;
 }

 bool substitute(SgNode *tnl, SgVariableSymbol *sym, SgExpression* expr, SgNode* root, SgSymbolTable* symtab) {
 if (tnl == NULL)
 return false;

 bool r = false;

 for(int i=0; i < tnl->get_numberOfTraversalSuccessors(); i++){

 SgNode* tn = tnl->get_traversalSuccessorByIndex(i);
 r = substitute(isSgStatement(tn), sym, expr, root, symtab) || r;
 }


 return r;
 }
 */

} // namespace
