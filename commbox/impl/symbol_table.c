#include <stdlib.h>
#include <string.h>

#include "../intr/symbol_table.h"

// construct symbol from appropiate properties
struct symbol *create_symbol(char *name, int type, int size, void *value)
{
	struct symbol *s = (struct symbol *)malloc(sizeof(struct symbol));
	s->name = (char *)malloc(sizeof(char) * strlen(name));
	strcpy(s->name, name);
	s->type = type;
	s->size = size;
	s->value = value;
	return s;
}

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
	destroy_table(symbol_tab);
	return new_tab;
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

void *get_value_of(struct symbol *sym)
{
	if(sym != NULL)
		return sym->value;	
	else return NULL;
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

/*
int main()
{
	int i = 0;
	char str[30];
	struct symbol s1 = {"s1asdf", 'a', 1, NULL, NULL};
	struct symbol s2 = {"sd2fsdf", 'a', 1, NULL, NULL};
	struct symbol s3 = {"s3", 'a', 1, NULL, NULL};
	struct symbol s4 = {"s4dfdsd", 'a', 1, NULL, NULL};
	struct symbol s5 = {"ssldfk5", 'a', 1, NULL, NULL};
	struct sym_tab *t = get_new_table(1);
	t = put(t, &s1);
	t = put(t, &s2);
	t = put(t, &s3);
	t = put(t, &s4);
	t = put(t, &s5);
	print_table(t);
	SearchResult sr;
	while(i < 3)
	{
		printf("Enter key ");
		scanf("%s", str);
		sr = search(t, str);
		printf("%d \n", sr.found);
	}
}*/
