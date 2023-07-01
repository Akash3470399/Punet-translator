#include "symbol_table.h"

#ifndef PARSE_TREE_H
#define PARSE_TREE_H

struct program
{
	char *name;
	struct sym_tab *var_sym;
	struct sym_tab *const_sym;
	void *tree;
}p;

#endif
