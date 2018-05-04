#include "lexer.h"
#include <string.h>

using namespace std;
int LineNo;
FILE* infile;
char Tokenbuffer[10];
void initlexer() {
	infile = fopen("d:\\test.txt", "r");   //将文件流对象与文件连接起来
}
void closelexer(){
	fclose(infile);
}
Token find(char* a) {
	int ok = 0;
	for (int j = 0;j<23; j++)
		if (strcmp(TokenTab[j].lexeme, a) == 0)
		{
			ok = 1; return TokenTab[j];
		}
	if (ok == 0)
		return { ERRTOKEN, "", 0.0, NULL };
}
char get_char(void) {
	char c=getc(infile);
	return toupper(c);
}
void back_char(char c) {
	if (c != EOF) ungetc(c, infile);
	return;
}
Token get_token() {
	struct Token token = { ERRTOKEN, "", 0.0, NULL };
	memset(Tokenbuffer, 0, 10);
	int i = 0;
	char c;
	for (;;) {
		c = get_char();
		if (c == EOF) {
			token.type = NONTOKEN;
			return token;
		}
		if (c == '\n') LineNo++;
		if (!isspace(c)) break;
	}
	while (c != '#') {
		if (isalpha(c)) {
			Tokenbuffer[i] = c; i++;
			for (;;) {
				c = get_char();
				if (isalpha(c) || isdigit(c)) { Tokenbuffer[i] = c; i++; }
				else { back_char(c); break; }
			}
			token.lexeme = Tokenbuffer; token = find(token.lexeme); token.lexeme = Tokenbuffer; return token;
		}
		else if (isdigit(c)) {
			Tokenbuffer[i] = c; i++;
			for (;;) {
				c = get_char();
				if (isdigit(c)) { Tokenbuffer[i] = c; i++; }
				else  break;
			}
			if (c == '.') {
				Tokenbuffer[i] = c; i++;
				for (;;) {
					c = get_char();
					if (isdigit(c)) { Tokenbuffer[i] = c; i++; }
					else  break;
				}
			}
			back_char(c);
			token.type = CONST_ID;
			token.lexeme = Tokenbuffer;
			token.value = atof(Tokenbuffer);   return token;
		}
		else {
			switch (c)
			{
			case '*':
				Tokenbuffer[i] = c; i++;
				c = get_char();
				if (c == '*') {
					token.type = POWER;  Tokenbuffer[i] = c; i++; token.lexeme = Tokenbuffer; break;
				}
				else {
					back_char(c);
					token.type = MUL;  token.lexeme = Tokenbuffer;  break;
				}
			case'/':
				Tokenbuffer[i] = c; i++;
				c = get_char();
				if (c == '/') {
					while (c != '\n'&&c != EOF) { c = get_char(); Tokenbuffer[i] = c; i++; }
					back_char(c);
					return get_token();
				}
				else {
					back_char(c);
					token.type = DIV; token.lexeme = Tokenbuffer; break;
				}
			case'-':
				Tokenbuffer[i] = c; i++;
				c = get_char();
				if (c == '-') {
					while (c != '\n'&&c != EOF) { c = get_char(); Tokenbuffer[i] = c; i++; }
					back_char(c);
					return get_token();
				}
				else {
					back_char(c);
					token.type = MINUS; token.lexeme = Tokenbuffer; break;
				}
			case '+':Tokenbuffer[i] = c; i++;  token.type = PLUS; token.lexeme = Tokenbuffer;  break;
			case ',': Tokenbuffer[i] = c; i++;  token.type = COMMA; token.lexeme = Tokenbuffer; break;
			case ';':Tokenbuffer[i] = c; i++;  token.type = SEMICO; token.lexeme = Tokenbuffer; break;
			case '(': Tokenbuffer[i] = c; i++;  token.type = L_BRACKET; token.lexeme = Tokenbuffer; break;
			case ')':Tokenbuffer[i] = c; i++;  token.type = R_BRACKET; token.lexeme = Tokenbuffer; break;
			default:token.type = ERRTOKEN; break;
			}
		}
		break;
	}
	return token;
	//return;
}
