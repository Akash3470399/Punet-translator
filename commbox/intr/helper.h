#include <stdio.h>
#include "symbol_table.h"
#include "blocks/structs.h"

#ifndef HELPER_H
#define HELPER_H


int is_valid_id(char *);
int is_alpha(char);
int is_digit(char);
int is_number(char *str);
int is_keyword(char *str);
int is_space(char);
int is_present(char ch, char charSeq[]);
int is_valid_type(char *str);

SearchResult master_search(struct program p, char *str);


extern char *keywords_arr[];
extern char *types_arr[];
extern char *paren_arr[];
extern char *cmp_ops_arr[];
extern char *logical_ops_arr[];
extern char *spcl_ops[];
#endif
