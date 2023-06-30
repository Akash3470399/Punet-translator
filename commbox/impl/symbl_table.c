#include <stdlib.h>
#include <string.h>

#include "../intr/symbl_table.h"

// logic is addition of char ascii value multiplied by its position 
// and position starts from1
// at the end hash value is the value which is opted by taking mod of that sum
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

// if size of hashtable is full then grow the table size by 2
void grow_hashtable(struct sym_tab **symbol_tab)
{
	int i = 0;
	struct sym_tab *new_tab = get_new_table((*symbol_tab)->capacity * 2);
	while(i < (*symbol_tab)->capacity)
	{
		if((*symbol_tab)->table[i] != NULL)
			preorder_put(new_tab, (*symbol_tab)->table[i]);
		i += 1;
	}
	destroy_table(*symbol_tab);
	*symbol_tab = new_tab;
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

// destroy table.
void destroy_table(struct sym_tab *tab)
{
	free(tab->table);
	free(tab);
}

void print_table(struct sym_tab *tab)
{
	int i = 0;
	while(i < tab->capacity)
	{
		if(tab->table[i] != NULL)
			preorder_print(tab->table[i]);
		i += 1;
	}
}
// put sym symbol in sym_tab hash map
// collided symbols are stored in the form of bst
// according to strcmp value of names of symbles.
void put(struct sym_tab *symbol_tab, struct symbol *sym)
{	
	int idx;
	if(symbol_tab->size >= symbol_tab->capacity)
		grow_hashtable(&symbol_tab);

        idx = hash(sym, symbol_tab->capacity);
	if(symbol_tab->table[idx] == NULL)
	{
		symbol_tab->table[idx] = sym;
		symbol_tab->size += 1;	
	}
	else
		collide_put(symbol_tab->table[idx], sym);		
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
void preorder_put(struct sym_tab *symbol_tab, struct symbol *sym)
{
	if(sym != NULL)
	{
		struct symbol *left = sym->left, *right = sym->right;
		sym->left = NULL;
		sym->right = NULL;
		put(symbol_tab, sym);
		
		preorder_put(symbol_tab, left);
	
		preorder_put(symbol_tab, right);
	}	
}

void preorder_print(struct symbol *sym)
{
	if(sym != NULL)
	{
		printf("%s\n", sym->name);
		preorder_print(sym->left);
		preorder_print(sym->right);
	}
}

int main()
{
	struct symbol s1 = {"s1", 'a', 1, NULL, NULL};
	struct symbol s2 = {"s2", 'a', 1, NULL, NULL};
	struct symbol s3 = {"s3", 'a', 1, NULL, NULL};
	struct sym_tab *t = get_new_table(1);
	put(t, &s1);
	put(t, &s2);
	put(t, &s3);
	print_table(t);
}
