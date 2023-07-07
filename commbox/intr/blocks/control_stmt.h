#include "../symbol_table.h"
#include "structs.h"

#ifndef CONTROL_STMT_H
#define CONTROL_STMT_H

_forinloop_ins *create_forinloop(
		struct symbol *key, struct symbol *val, 
		struct symbol *to_itr, _instruction *ins_head);
void destroy_forloop(_forinloop_ins *loop);
void execute_forloop(_forinloop_ins *loop);

_ifthen_ins *create_ifthenstmt(_condition *predicate, _instruction *ins_head);
void destroy_ifthenstmt(_ifthen_ins *stmt);
void execute_ifthenstmt(_ifthen_ins *stme);
#endif
