#include "tokenizer.h"

#ifndef SYNTAX_CHECKER_H
#define SYNTAX_CHECKER_H



void check_is_valid_id();
void check_is_same(enum token exp_tok);
void check_commbox();

extern int err;

struct program
{
	char *name;

};
#endif
