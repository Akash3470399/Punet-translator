#ifndef TOKENIZER_H
#define TOKENIZER_H

int tokenizeing_fd;
char *cur_tok;

enum token {
	COMMBOX, CONST, VAR, INTEGER, BOOLEAN, ADDRESS, BEGIN, IF, THEN, 
	FI, FOR, IN, DO, OD, ACTIVATE, WITH, TIMEOUT, SEND, TO, RECV, 
	FROM, END, TRUE, FALSE, 
	OROUND_PAREN=100, CROUND_PAREN, OSQR_PAREN, CSQR_PAREN, 
	LT = 200, GT, EQL, LTE, GTE, 
	AND = 300, OR, NOT,
	GUARD = 400, COMMA, SEMICOLON, ASIGN, ACTION, 
	ID = 500
};

void tokenizer_config();
enum token next();
/* ********** HELPER FUNCTIONS ********************* */
int is_space(char);
int is_present(char ch, char charSeq[]);

#endif
