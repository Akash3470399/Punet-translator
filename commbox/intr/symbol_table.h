#include <stdio.h>

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

struct symbol
{
	char *name;
	int type, size;
	void *value;
	struct symbol *left, *right;	
	void (*destroy)(struct symbol *);
};

struct sym_tab
{
	struct symbol **table;
	int size;
	int capacity;
	void (*destroy)(struct sym_tab *);
};

typedef struct SearchResult
{
	int found;
	struct symbol *sym;
}SearchResult;

int hash(struct symbol *sym, int capacity);

struct symbol *create_symbol(char *name, int type, int size, void *value);
void destroy_symbol(struct symbol *sym);
void *get_value_of(struct symbol *sym);

struct sym_tab *get_new_table(int capacity);
void destroy_table(struct sym_tab *tab);
struct sym_tab *delete_sym(struct sym_tab *tab, struct symbol *sym);
void delete_table(struct sym_tab *tab);
struct sym_tab *grow_hashtable(struct sym_tab *symbol_tab);
void print_table(struct sym_tab *tab);
struct sym_tab *put(struct sym_tab *, struct symbol *sym);
SearchResult search(struct sym_tab *tab, char *key);

// tree methos 
void collide_put(struct symbol *parent, struct symbol *sym);
struct sym_tab *preorder_put(struct sym_tab *symbol_tab, struct symbol *sym);
void preorder_print(struct symbol *sym);
void destroy_sym_tree(struct symbol *sym);
struct symbol *delete_from_tree(struct symbol *tree, struct symbol *sym);
struct symbol *remove_head(struct symbol *sym);
#endif
