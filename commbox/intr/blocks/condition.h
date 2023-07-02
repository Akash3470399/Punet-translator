#include "../tokenizer.h"
#ifndef CONDITION_H
#define CONDITION_H



typedef struct _condition1 _condition1;
typedef struct _condition2 _condition2;
typedef struct _condition _condition;

enum condition_type {NOT_CONDITION, AND_CONDITION, OR_CONDITION, ID_CONDITION, BOOL_VAL};


struct _condition1
{
	_condition *c;
};

struct _condition2
{
	_condition *c1;
	_condition *c2;
};
struct _condition 
{
	enum condition_type type;
	union conditon{
		_condition1 *c1;
		_condition2 *c2;
		struct symbol *s;
		int *bool_val;
	}c;
};

_condition *create_condition(void *cond, enum condition_type type);
_condition1 *get_condition1(_condition *c);
_condition2 *get_condition2(_condition *c1, _condition *c2);

// ***************** condtion evalutor methods ************
int eval(_condition *exp);
int eval_or_condition(_condition *exp);
int eval_and_condition(_condition *exp);
int eval_not_condition(_condition *exp);
#endif
