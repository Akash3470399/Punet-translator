#include <stdlib.h>

#include "../../intr/blocks/condition.h"
#include "../../intr/symbol_table.h"

// **************  condition creation methods **********
_condition *create_condition(void *cond, enum condition_type type)
{
	_condition *newc = (_condition *)malloc(sizeof(_condition));
	newc->type = type;
	newc->c.eval = eval;
	switch(type)
	{
		case NOT_CONDITION: 
			newc->c.c1 = (_condition1 *)cond; 
			newc->destroy = destroy_condition;
			break;
		case AND_CONDITION: 
		case OR_CONDITION:
			newc->c.c2 = (_condition2 *)cond;
		       	newc->destroy = destroy_condition2;	
			break;
		case ID_CONDITION:
			newc->c.s = (struct symbol *)cond;
			newc->destroy = delete_condition;
			break;
		case BOOL_VAL:
			newc->c.bool_val = (int *)cond;
			newc->destroy = delete_condition;
			break;
		default :break;
	}
	return newc;
}


_condition1 *get_condition1(_condition *c)
{
	_condition1 *new_condition = (_condition1 *)malloc(sizeof(_condition1));
	new_condition->c = c;
	return new_condition;
}

_condition2 *get_condition2(_condition *c1, _condition *c2)
{
	_condition2 *new_condition = (_condition2 *)malloc(sizeof(_condition2));
	new_condition->c1 = c1;
	new_condition->c2 = c2;
	return new_condition;
}


// ***************** condtion evalutor methods ************

int eval(_condition *exp)
{
	int result;
	int *val;
	switch(exp->type)
	{
		case NOT_CONDITION:
			result = eval_not_condition(exp->c.c1);
			break;
		case OR_CONDITION:
		       result = eval_or_condition(exp->c.c2);
		       break;
		case AND_CONDITION:
		       result = eval_and_condition(exp->c.c2);
		       break;
		case ID_CONDITION:
		       val = (int *)get_value_of(exp->c.s);
		       result = *val;
		       break;
		case BOOL_VAL:
		       result = *(exp->c.bool_val);
		       break;
		default: break;
	}
}

int eval_or_condition(_condition2 *exp)
{
	return (eval(exp->c1) || eval(exp->c2));
}

int eval_and_condition(_condition2 *exp)
{
	return (eval(exp->c1) &&  eval(exp->c2));
}

int eval_not_condition(_condition1 *exp)
{
	return !(eval(exp->c));
}



// **************  condition destroy methos ************
void delete_condition(_condition *c)
{
	free(c);
}

void destroy_condition1(_condition *c)
{
	c->destroy(c->c.c1);
	free(c);
}

void destroy_condition2(_condition *c)
{
	c->destroy(c->c.c1);
	c->destroy(c->c.c2);
	free(c);
}

void main()
{
	
}
