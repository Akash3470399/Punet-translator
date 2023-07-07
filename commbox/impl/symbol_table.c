#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../intr/blocks/program.h"
#include "../intr/symbol_table.h"


// logic is addition of char ascii value multiplied by its position 
// and position starts from 1
// hash value is the value which is opted by taking mod of that sum
int hash(struct symbol *sym, int capacity)
{
	int index = 0, i = 0;
	while(sym->name[i] != '\0')
	{
		index += ((i+1) * sym->name[i]);
		i += 1;
	}
	index = index % capacity;
	return index;
}


// construct symbol from appropiate properties
struct symbol *create_symbol(char *name, int type, int size, void *value)
{
	struct symbol *s = (struct symbol *)malloc(sizeof(struct symbol));
	s->name = (char *)malloc(sizeof(char) * strlen(name));
	strcpy(s->name, name);
	s->type = type;
	s->size = size;
	s->value = value;
	s->destroy = destroy_symbol;
	return s;
}

void destroy_symbol(struct symbol *sym)
{
	free(sym->name);
	free(sym);
}

void *get_value_of(struct symbol *sym)
{
	if(sym != NULL)
		return sym->value;	
	else return NULL;
}

// initilizations requied for symbol table hash table.
struct sym_tab *get_new_table(int capacity)
{
	int i = 0;
	struct sym_tab *tab = (struct sym_tab *)malloc(sizeof(struct sym_tab));
	tab->size = 0;
       	tab->capacity = capacity;
	tab->table = (struct symbol **)malloc(sizeof(struct symbol *) * capacity);	
	while(i < capacity)
		tab->table[i++] = NULL;
	return tab;
}

struct sym_tab *delete_sym(struct sym_tab *tab, struct symbol *sym)
{
	int key; 
	if(tab != NULL && sym != NULL)
	{
		key = hash(sym , (tab)->capacity);
		(tab)->table[key] = delete_from_tree((tab)->table[key], sym);
		if((tab)->table[key] == NULL) (tab)->size -= 1;
	}
	return tab;
}

// delete table.
void delete_table(struct sym_tab *tab)
{
	free(tab->table);
	free(tab);
}

// delete table.
void destroy_table(struct sym_tab *tab)
{
	int i = 0;
	while(i < tab->capacity)
	{
		if(tab->table[i] != NULL)
			destroy_sym_tree(tab->table[i]);
		i += 1;
	}
	delete_table(tab);
}

// if size of hashtable is full then grow the table size by 2
struct sym_tab *grow_hashtable(struct sym_tab *symbol_tab)
{
	int i = 0;
	struct sym_tab *new_tab = get_new_table(symbol_tab->capacity * 2);
	while(i < symbol_tab->capacity)
	{
		if(symbol_tab->table[i] != NULL)
			new_tab = preorder_put(new_tab, symbol_tab->table[i]);
		i += 1;
	}
	delete_table(symbol_tab);
	return new_tab;
}

void print_table(struct sym_tab *tab)
{
	int i = 0;
	printf("capacity %d\n", tab->capacity);
	while(i < tab->capacity)
	{
		if(tab->table[i] != NULL)
		{	printf("idx %d ", i);
			preorder_print(tab->table[i]);
			printf("\n");
		}
		i += 1;
	}
}

// put sym symbol in sym_tab hash map
// collided symbols are stored in the form of bst
// according to strcmp value of names of symbles.
struct sym_tab *put(struct sym_tab *symbol_tab, struct symbol *sym)
{	
	int idx;
	if(symbol_tab->size >= symbol_tab->capacity)
		symbol_tab = grow_hashtable(symbol_tab);

        idx = hash(sym, symbol_tab->capacity);
	if(symbol_tab->table[idx] == NULL)
	{
		symbol_tab->table[idx] = sym;
		symbol_tab->size += 1;	
	}
	else
		collide_put(symbol_tab->table[idx], sym);		
	return symbol_tab;
}

// serch if a symbol is present by symbol name
SearchResult search(struct sym_tab *tab, char *key)
{
	struct symbol s = {key, 'a', 0, NULL, NULL}; 
	int idx = hash(&s, tab->capacity);
	struct symbol *ptr;
	
	SearchResult sr;
	sr.found = 0;

	if(tab->table[idx] != NULL)
	{
		ptr = tab->table[idx];
		while(ptr != NULL && sr.found == 0)
		{
			if(strcmp(key, ptr->name) == 0)
			{
				sr.found = 1;
				sr.sym = ptr;
			}
			else if(strcmp(key, ptr->name) < 0)
				ptr = ptr->left;
			else ptr = ptr->right;			
		}
	}
	return sr;	
}

// search in both var & const symbols.
SearchResult master_search(struct program p, char *str)
{
	SearchResult sr = search(p.var_sym, str);
	if(sr.found == 0)
		sr = search(p.const_sym, str);
	return sr;
}

// if index is pre filled then store multiple symbols in bst form.
// put symbol sym in bst with given parent
void collide_put(struct symbol *parent, struct symbol *sym)
{
	if(parent != NULL)
	{
		if(strcmp(sym->name, parent->name) <= 0)
		{
			if(parent->left == NULL)
				parent->left = sym;
			else
				collide_put(parent->left, sym);
		}
		else
		{
			if(parent->right == NULL)
				parent->right = sym;
			else 
				collide_put(parent->right, sym);
		}
	}
}
// put each symbol from bst sym in symbol_tab
struct sym_tab *preorder_put(struct sym_tab *symbol_tab, struct symbol *sym)
{
	if(sym != NULL)
	{
		struct symbol *left = sym->left, *right = sym->right;
		sym->left = NULL;
		sym->right = NULL;
		symbol_tab = put(symbol_tab, sym);
		
		symbol_tab = preorder_put(symbol_tab, left);
	
		symbol_tab = preorder_put(symbol_tab, right);
	}	
	return symbol_tab;
}

void preorder_print(struct symbol *sym)
{
	if(sym != NULL)
	{
		printf("%s\t", sym->name);
		preorder_print(sym->left);
		preorder_print(sym->right);
	}
}

void destroy_sym_tree(struct symbol *sym)
{
	if(sym != NULL)
	{
		destroy_sym_tree(sym->left);
		destroy_sym_tree(sym->right);
		sym->destroy(sym);
	}
}

struct symbol *delete_from_tree(struct symbol *tree, struct symbol *sym)
{
	struct symbol *ptr = tree, *parent = NULL;	
	if(ptr == sym)
		ptr = remove_head(tree);
	else
	{
		while(ptr != NULL && ptr != sym)
		{
			parent = ptr;
			if(strcmp(sym->name, ptr->name) <= 0)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}	

		if(ptr != NULL)
		{
			if(ptr->left == NULL && ptr->right == NULL)
			{
				if(parent->left == ptr)
					parent->left = NULL;
				else parent->right = NULL;
				ptr->destroy(ptr);
			}
			else
			{
				if(parent->left == ptr)
					parent->left = remove_head(ptr);
				else parent->right = remove_head(ptr);
			}
		
		}
		ptr = tree;
	}
	return ptr;	
}

struct symbol *remove_head(struct symbol *sym)
{
	struct symbol *ptr = sym, *parent = NULL; 
	if(ptr->left == NULL && ptr->right == NULL)
	{
		ptr->destroy(ptr);
		ptr = NULL;
	}
	else if(ptr->left != NULL && ptr->right == NULL)
	{
		ptr = ptr->left;
		sym->destroy(sym);
	}
	else if(ptr->right != NULL && ptr->right->left == NULL && ptr->right->right == NULL)
	{
		ptr = ptr->right;
		ptr->left = sym->left;
		sym->destroy(sym);
	}
	
	else
	{
		ptr = ptr->right;
		while(ptr->left != NULL)
		{
			parent = ptr;
			ptr = ptr->left;
		}
		parent->left = ptr->right;
		ptr->left = sym->left;
		ptr->right = sym->right;
		sym->destroy(sym);
	}
	return ptr;
}

