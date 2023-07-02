#include "tokenizer.h"

#ifndef SYNTAX_CHECKER_H
#define SYNTAX_CHECKER_H



void check_is_valid_id();
void check_for_tok(enum token exp_tok);
void check_commbox();
void check_valid_type();
void check_valid_value(struct symbol **sym);
void check_data_item(char);			
void check_declr();
void check_guard();
void check_begin();

extern int err;

#endif
