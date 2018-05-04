#ifndef PARSE_H
#define PARSE_H
#include "lexer.h"
typedef double(*FuncPtr)(double);
using namespace std;
struct ExprNode
{
	 Token_Type OpCode;	// 记号种类
	union
	{
		struct {
			ExprNode *Left, *Right;
		} CaseOperator;	// 二元运算
		struct {
			ExprNode * Child;
			FuncPtr MathFuncPtr;
		} CaseFunc;	// 函数调用
		double CaseConst; 	// 常数，绑定右值
		double * CaseParmPtr; 	// 参数T，绑定左值
	} Content;
};
void analyse_tree();
void SyntanError(int i);
void match(Token_Type a);
static struct ExprNode* Make_tree_FUN(Token_Type root, FuncPtr fun, ExprNode * child);
static struct ExprNode* Make_tree_T(Token_Type root);
static struct ExprNode* Make_tree_CONST_ID(Token_Type root, double value);
static struct ExprNode * Make_tree(Token_Type opcode, ExprNode *left, ExprNode *right);
struct ExprNode * Expression();
struct ExprNode * Term();
struct ExprNode * Factor();
struct ExprNode * Component();
struct ExprNode * Atom();
void ForStatment();
void RotStatment();
void ScaleStatment();
void OriginStatment();
void Statement();
void Program();
void print_tree(ExprNode* root, int indent);
#endif
