#ifndef TOKENIZER_H
#define TOKENIZER_H

enum token {
	COMMBOX, CONST, VAR, INTEGER, BOOLEAN, ADDRESS, BEGIN, IF, THEN, 
	FI, FOR, IN, DO, OD, ACTIVATE, WITH, TIMEOUT, SEND, TO, RECV, 
	FROM, END, TRUE, FALSE, 
	OROUND_PAREN=100, CROUND_PAREN, OSQR_PAREN, CSQR_PAREN, 
	LT = 200, GT, EQL, LTE, GTE, 
	AND = 300, OR, NOT,
	GUARD = 400, COMMA, COLON, SEMICOLON, ASIGN, ACTION, 
	ID = 500
};

int tokenizeing_fd = -2;
char *cur_tok;

enum token str_to_enum(char *tok_str);
void tokenizer_config();
enum token next();
void print_tokens();
#endif
