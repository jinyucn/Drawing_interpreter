#include "parse.h"
#include "lexer.h"
#include "semantic.h"
#ifdef PARSER_DEBUG_H
    double tparam = 0;
#else
    double parameter = 0,
    locx = 0, locy = 1,
    scax = 1, scay = 1,
    rot_angle = 0;
    COLORREF draw_color=red;
#endif
using namespace std;
Token lookahead;
int enter_blank=0;
void enter(char* a) {
	enter_blank++;
	for (int i = 0; i < enter_blank; i++)
		cout << " ";
	cout <<"enter	"<< a<<endl;
	return;
}
void exit(char* a) {
	enter_blank--;
	for (int i = 0; i < enter_blank; i++)
		cout << " ";
	cout <<"exit	"<< a << endl;
	return;
}
void call_print(ExprNode* a) {
	cout << "parse tree:" << endl;
	cout << "-------------------------------------" << endl;
	print_tree(a, 0);
	cout << "-------------------------------------" << endl;
}
void print_tree(ExprNode* root, int indent) {
	int temp;
	for (temp = 1; temp <= indent; temp++)
		cout << "	";
	switch (root->OpCode) {
	case PLUS: cout << "+" << endl; break;
	case MINUS: cout << "-" << endl; break;
	case MUL: cout << "*" << endl; break;
	case DIV: cout << "/" << endl; break;
	case POWER: cout << "**" << endl; break;
	case FUNC: cout << root->Content.CaseFunc.MathFuncPtr << endl; break;
	case CONST_ID: cout << root->Content.CaseConst << endl; break;
	case T: cout << "T" << endl; break;
	default:cout << "ERROR TREE NODE" << endl; break;
	}
	if (root->OpCode == CONST_ID || root->OpCode == T) return;
	if (root->OpCode == FUNC)
		print_tree(root->Content.CaseFunc.Child, indent + 1);
	else {
		print_tree(root->Content.CaseOperator.Left, indent + 1);
		print_tree(root->Content.CaseOperator.Right, indent + 1);
	}
}
void SyntanError(int i) {
	switch (i) {
	case 1:
		cout << "ERROR_TOKEN"<<endl; lookahead = get_token(); break;
	case 2:
		cout << "UNEXPECT TOKEN"<<endl; lookahead = get_token(); break;
	}
}
void match(Token_Type a) {
	if (a==lookahead.type) {
		lookahead = get_token();
		if (lookahead.type == ERRTOKEN||lookahead.type == UNKOWNID) SyntanError(1);
	}
	else SyntanError(2);
}
static struct ExprNode* Make_tree_FUN(Token_Type root, FuncPtr fun, ExprNode * child) {
	ExprNode *tree = new (ExprNode);
	tree->OpCode = root;
	tree->Content.CaseFunc.MathFuncPtr = fun;
	tree->Content.CaseFunc.Child = child;
	return tree;
}
static struct ExprNode* Make_tree_T(Token_Type root) {
	ExprNode *tree = new (ExprNode);
	tree->OpCode = root;
	tree->Content.CaseParmPtr = &parameter;
	return tree;
}
static struct ExprNode* Make_tree_CONST_ID(Token_Type root, double value) {
	ExprNode *tree = new (ExprNode);
	tree->OpCode = root;
	tree->Content.CaseConst = value;
	return tree;
}
static struct ExprNode * Make_tree(Token_Type opcode, ExprNode *left, ExprNode *right) {
	ExprNode *tree = new (ExprNode);
	tree->OpCode = opcode;
	tree->Content.CaseOperator.Left = left;
	tree->Content.CaseOperator.Right = right;
	return tree;
}
struct ExprNode * Expression() {
	enter("Expression");
	ExprNode *left, *right;
	Token express;
	left=Term();
	while (lookahead.type == PLUS || lookahead.type == MINUS) {
		express = lookahead;
		match(lookahead.type);
		right = Term();
		left = Make_tree(express.type, left, right);
	}
	exit("Expression");
	return left;
}
struct ExprNode * Term() {
	enter("Term");
	ExprNode *left, *right;
	left = Factor();
	Token term1;
	while (lookahead.type == MUL || lookahead.type == DIV) {
		term1 = lookahead;
		match(lookahead.type);
		right = Factor();
		left = Make_tree(term1.type, left, right);
	}
	exit("Term");
	return left;
}
struct ExprNode * Factor() {
	enter("Factor");
	ExprNode *left, *right;
	switch (lookahead.type){
	case PLUS:match(PLUS); right = Factor(); break;
	case MINUS:match(MINUS); right = Factor(); left = new ExprNode; left->OpCode = CONST_ID;
		left->Content.CaseConst = 0.0;
		right = Make_tree(MINUS, left, right); break;
	default:right = Component();
		break;
	exit("Factor");
	return right;
	}

}
struct ExprNode * Component() {
	enter("Component");
	ExprNode *left, *right;
	left = Atom();
	Token power1;
	while (lookahead.type ==POWER) {
		power1 = lookahead;
		match(POWER);
		right = Atom();
		left = Make_tree(power1.type, left, right);
	}
	exit("Component");
	return left;
}
struct ExprNode * Atom() {
	enter("Atom");
	ExprNode *node;
	Token t = lookahead;
	switch (lookahead.type) {
	case CONST_ID:match(CONST_ID);  node = Make_tree_CONST_ID(CONST_ID, t.value); break;
	case T:match(T); node=Make_tree_T(T); break;
	case FUNC:match(FUNC); match(L_BRACKET); node = Make_tree_FUN(FUNC, t.FuncPtr, Expression());
		match(R_BRACKET); break;
	case L_BRACKET:match(L_BRACKET); node = Expression(); match(R_BRACKET); break;
	default:SyntanError(2);
	}
	exit("Atom");
	return node;
}
void ForStatment() {
	ExprNode* for1, *for2, *for3,*for4, *for5;
	double start2,End2,stenum;
	enter("ForStatment");
	match(FOR); match(T); match(FROM);
	for1 = Expression();start2 = GetExpValue(for1); call_print(for1);
	match(TO);  for2 = Expression();End2 = GetExpValue(for2); call_print(for2);
	match(STEP); for3 = Expression();stenum = GetExpValue(for3); call_print(for3);
	match(DRAW); match(L_BRACKET); for4 = Expression(); call_print(for4);
	match(COMMA); for5=Expression();call_print(for5);
	    DrawLoop(start2,End2,stenum,for4,for5);
	 match(R_BRACKET);
	 Deltree(for1);Deltree(for2);Deltree(for3);Deltree(for4);Deltree(for5);
	exit("ForStatment");
}
void RotStatment() {
	ExprNode *tmp;
	enter("RotStatment");
	match(ROT); match(IS);  tmp= Expression();rot_angle = GetExpValue(tmp);
	call_print(tmp);
	Deltree(tmp);
	exit("RotStatment");
}
void ScaleStatment() {
	ExprNode *left, *right;
	enter("ScaleStatment");
	match(SCALE); match(IS); match(L_BRACKET); left=Expression();scax = GetExpValue(left);
	call_print(left); match(COMMA);
	right = Expression(); scay = GetExpValue(right); call_print(right); match(R_BRACKET);
	Deltree(left);Deltree(right);
	exit("ScaleStatment");
}
void OriginStatment() {
	ExprNode *left, *right;
	enter("OriginStatment");
	match(ORIGIN); match(IS); match(L_BRACKET);
	left = Expression(); locx = GetExpValue(left);call_print(left);
	match(COMMA); right=Expression();locy = GetExpValue(right);
	call_print(right); match(R_BRACKET);
	Deltree(left);Deltree(right);
	exit("OriginStatment");
}
void ColorStatement(){
    enter("ColorStatement");
    match(COLOR); match(IS);
    if(lookahead.type==RED)  draw_color=red;
    else if(lookahead.type==GREEN)  draw_color=green;
    else if(lookahead.type==BLUE)  draw_color=blue;
    else  draw_color=black;
    lookahead=get_token();
    exit("ColorStatement");
}
void Statement() {
    enter_blank=0;
	enter("Statement");
	switch (lookahead.type)
	{
	case ORIGIN:OriginStatment(); break;
	case SCALE:ScaleStatment(); break;
	case ROT:RotStatment(); break;
	case FOR:ForStatment(); break;
	case COLOR:ColorStatement(); break;
	default:SyntanError(2);break;
	}
	exit("Statement");
}
void Program(){
	enter("Program");
	while (lookahead.type != NONTOKEN)
	{
		Statement(); match(SEMICO);
	}
	exit("Program");
}
void analyse_tree() {
	initlexer();
	lookahead=get_token();
	Program();
	closelexer();
	return;
}




