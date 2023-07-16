#ifndef TOKENIZER_H
#define TOKENIZER_H

enum token {
	COMMBOX, CONST, VAR, BEGIN, IF, THEN, FI, FOR, 
	IN, DO, OD, ACTIVATE, WITH, TIMEOUT, SEND, TO, RECV, 
	FROM, END, TRUE, FALSE, 
	INTEGER = 100, BOOLEAN, ADDRESS, MESSAGE,
	OROUND_PAREN = 200, CROUND_PAREN, OSQR_PAREN, CSQR_PAREN, 
	LT = 300, GT, EQL, LTE, GTE, 
	AND = 400, OR, NOT,
	GUARD = 500, COMMA, COLON, SEMICOLON, ASIGN, DECLR_ASIGN, ACTION, 
	ID = 600, NUMERIC
};

extern char *cur_tok;

enum token str_to_enum(char *tok_str);
void tokenizer_config();
enum token next();
void go_back();
void print_tokens();
#endif
