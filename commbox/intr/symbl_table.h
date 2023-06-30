#include <stdio.h>

#ifndef SYMBL_TABLE_H
#define SYMBL_TABLE_H

struct symbol
{
	char *name;
	char type;
	int size;
	struct symbol *left, *right;	
};

struct sym_tab
{
	struct symbol **table;
	int size;
	int capacity;
};

int hash(struct symbol *sym, int capacity);
struct sym_tab *get_new_table(int capacity);
void destroy_table(struct sym_tab *tab);
void put(struct sym_tab *, struct symbol *sym);


// tree methos 
void collide_put(struct symbol *parent, struct symbol *sym);
void preorder_put(struct sym_tab *symbol_tab, struct symbol *sym);
void preorder_print(struct symbol *sym);
#endif
