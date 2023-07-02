#include <stdio.h>

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

struct symbol
{
	char *name;
	int type, size;
	void *value;
	struct symbol *left, *right;	
};

struct sym_tab
{
	struct symbol **table;
	int size;
	int capacity;
};

typedef struct SearchResult
{
	int found;
	struct symbol *sym;
}SearchResult;

struct symbol *create_symbol(char *name, int type, int size, void *value);
int hash(struct symbol *sym, int capacity);
struct sym_tab *get_new_table(int capacity);
void destroy_table(struct sym_tab *tab);
void print_table(struct sym_tab *tab);
struct sym_tab *put(struct sym_tab *, struct symbol *sym);
SearchResult search(struct sym_tab *tab, char *key);
void *get_value_of(struct symbol *sym);

// tree methos 
void collide_put(struct symbol *parent, struct symbol *sym);
struct sym_tab *preorder_put(struct sym_tab *symbol_tab, struct symbol *sym);
void preorder_print(struct symbol *sym);
#endif
