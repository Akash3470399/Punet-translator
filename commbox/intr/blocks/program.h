#include "../symbol_table.h"
#include "structs.h"
#ifndef PROGRAM_H
#define PROGRAM_H





typedef struct _body _body;


struct _body
{
	_guard *head, *tail, *ptr;
};

struct program
{
	char *name;
	struct sym_tab *var_sym;
	struct sym_tab *const_sym;
	struct _body *root;
}p;

#endif
