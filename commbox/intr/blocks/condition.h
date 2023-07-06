#include "../tokenizer.h"
#include "structs.h"

#ifndef CONDITION_H
#define CONDITION_H

extern int __true , __false;


// condition creation methods.
_condition *create_condition(void *cond, enum condition_type type);
_condition2 *create_condition2(_condition *c1, _condition *c2);

// ***************** condtion evalutor methods ************
int eval(_condition *exp);
int eval_or_condition(_condition2 *exp);
int eval_and_condition(_condition2 *exp);
int eval_not_condition(_condition *exp);

// destroy method
void delete_condition(_condition *c);
void destroy_condition(_condition *c);
void destroy_condition1(_condition *c);
void destroy_condition2(_condition *c);

void print_condition(_condition *c);
#endif
