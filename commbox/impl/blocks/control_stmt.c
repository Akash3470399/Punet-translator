#include <stdlib.h>

#include "../../intr/blocs/control_stmt.h"


_forinloop_ins *create_forinloop(
		struct symbol *key, struct symbol *val, 
		struct symbol *to_itr, _instruction *ins_head
		)
{
	_forinloop_ins *loop = (_forinloop_ins *)malloc(sizeof(_forinloop_ins));
	loop->key = key, loop->val = val, loop->to_itr = to_itr;
	loop->ins_head = ins_head;
	loop->execute = execute_forinloop;
	loop->destroy = destroy_forinloop;
	return loop;
}

void execute_forinloop(_forinloop_ins *loop)
{

}

void destroy_forinloop(_forinloop_ins *loop)
{
	
}

_ifthen_ins *create_ifthenstmt(_condition *predicate, _instruction *ins_head)
{
	_ifthen_ins *stmt = (_ifthen_ins *)malloc(sizeof(_ifthen_ins));
	stmt->predicate = predicate, stmt->ins_head;
	stmt->execute = execute_ifthenstmt;
	stmt->destroy = destroy_ifthenstmt;
}

void execute_ifthenstmt(_ifthen_ins *stmt)
{

}

void destroy_ifthenstmt(_ifthen_ins *stmt)
{

}
