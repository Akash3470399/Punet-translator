#include <stdio.h>
#ifndef HELPER_H
#define HELPER_H


int is_valid_id(char *);
int is_alpha(char);
int is_digit(char);
int is_space(char);
int is_present(char ch, char charSeq[]);


extern char *keywords_arr[];
extern char *paren_arr[];
extern char *cmp_ops_arr[];
extern char *logical_ops_arr[];
extern char *spcl_ops[];
#endif
