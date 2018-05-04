#ifndef LEXER_H
#define LEXER_H
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <math.h>
#include<stdlib.h>
enum Token_Type{
ORIGIN,SCALE,ROT,IS,TO,STEP,DRAW,FOR,FROM,  //保留字
T,                                           //参数
SEMICO,L_BRACKET,R_BRACKET,COMMA,           //分隔符
PLUS,MINUS,MUL,DIV,POWER,                   //运算符
FUNC,                                       //函数
CONST_ID,                                   //常数
NONTOKEN,                                   //空记号
ERRTOKEN,UNKOWNID ,COLOR,RED,BLACK,GREEN,BLUE                                  //出错记号
};
struct Token
{
	Token_Type  type;
	char * lexeme;
	double value;
	double(*FuncPtr)(double);
};
static Token TokenTab[] ={
	{ CONST_ID,	"PI",		3.1415926,	NULL },
{ CONST_ID,	"E",		2.71828,	NULL },
{ T,			"T",		0.0,		NULL },
{ FUNC,		"SIN",		0.0,		sin },
{ FUNC,		"COS",		0.0,		cos },
{ FUNC,		"TAN",		0.0,		tan },
{ FUNC,		"LN",		0.0,		log },
{ FUNC,		"EXP",		0.0,		exp },
{ FUNC,		"SQRT",	0.0,		sqrt },
{ ORIGIN,		"ORIGIN",	0.0,		NULL },
{ SCALE,		"SCALE",	0.0,		NULL },
{ ROT,		"ROT",		0.0,		NULL },
{ IS,			"IS",		0.0,		NULL },
{ FOR,		"FOR",		0.0,		NULL },
{ FROM,		"FROM",	0.0,		NULL },
{ TO,		"TO",		0.0,		NULL },
{ STEP,		"STEP",	0.0,		NULL },
{ DRAW,		"DRAW",	0.0,		NULL } ,
{ COLOR,	"COLOR",	0.0,		NULL },
{ RED,		"RED",	0.0,		NULL },
{ BLACK,	"BLACK",	0.0,		NULL },
{ GREEN,	"GREEN",	0.0,		NULL },
{ BLUE,	"BLUE",	0.0,		NULL }};
void initlexer();
void closelexer();
Token get_token();
#endif
