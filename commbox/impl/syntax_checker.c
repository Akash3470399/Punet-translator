#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../intr/tokenizer.h"
#include "../intr/helper.h"
#include "../intr/symbol_table.h"
#include "../intr/blocks/structs.h"
#include "../intr/blocks/program.h"
#include "../intr/blocks/condition.h"
#include "../intr/blocks/guard.h"
#include "../intr/syntax_checker.h"


int err = 0;
struct program p;


void check_for_tok(enum token exp_tok)
{
	enum token inp_tok = next();
	err |= !(exp_tok == inp_tok);
}

void check_valid_type(enum token tok)
{
	err |= !(tok == INTEGER || tok == BOOLEAN || tok == ADDRESS);
}

/*
 *	check for valid value, that can be asigned to variable.
 *	evaluate valid value assign it to sym symbol.
 */
void check_valid_value(struct symbol **sym)
{
	enum token tok = next();
	SearchResult sr1, sr2;
	int *val;

	// also check if value is of same type as dedined in symbol type.
	switch(tok)
	{
		case ID:

			// check if value symbol(ID) is predefined
			sr1 = search(p.var_sym, cur_tok);
			sr2 = search(p.const_sym, cur_tok);
			if((sr1.found == 1) && (sr1.sym->type == (*sym)->type))
				(*sym)->value = sr1.sym->value;
			else if((sr2.found == 1) && (sr2.sym->type == (*sym)->type))
				(*sym)->value = sr2.sym->value;
			else err = 1;
			break;

		case NUMERIC:
			if((*sym)->type == INTEGER)
			{
				val = (int *)malloc(sizeof(int));
				*val = atoi(cur_tok);
				(*sym)->value = (void *)val; 
			}
			else err = 1;
			break;

		case TRUE:
		case FALSE:
			if((*sym)->type == BOOLEAN)
			{
				val = (int *)malloc(sizeof(int));
				if(tok == TRUE) *val = 1; else *val = 0;
				(*sym)->value = (void *)val;
			}
			else err = 1;
			break;

		default:
			err = 1;
	}
}

void check_is_valid_id()
{
	enum token tok = next();
	if(tok == ID)
	{
		// cur_tok is from tokenizer file which store the current token string
		err |= !is_valid_id(cur_tok);
	}
	else
		err |= 1;
}

void check_commbox()
{
	char name[32];
	check_for_tok(COMMBOX);
	check_is_valid_id();
	strcpy(name, cur_tok);
	check_for_tok(SEMICOLON);
	if(err == 0)
	{
		p.name = (char *)malloc(sizeof(char) *(strlen(name)+1));
		strcpy(p.name, name);
	}
	else
	{
		printf("Invalid name.\n");
	    err = 1;
	}
}


// valid data item is
// ID:TYPE
// ID:TYPE[]
// ID:TYPE[<integer value>]
void check_data_item(char c_v)
{
	int size = 1, type, *val;
	char name[32];
	enum token tok;
	struct symbol *sym;
	SearchResult sr1, sr2;

	check_is_valid_id();
	strcpy(name, cur_tok);

	check_for_tok(COLON);

	type = next();
	check_valid_type(type);
	
	sym = create_symbol(name, type, size, NULL); // last parameter is value
		
	tok = next();
	if(tok == OSQR_PAREN)// array declaration
	{
		tok = next();
		if(tok == CSQR_PAREN) size = 1;
		else
		{
			if(tok == NUMERIC)
			{		
				size = atoi(cur_tok);
				sym->size = size;
				check_for_tok(CSQR_PAREN);
			}
			else if(tok == ID)
			{
				sr1 = search(p.var_sym, cur_tok);
				sr2 = search(p.const_sym, cur_tok);
				if((sr1.found == 1) && (sr1.sym->type == INTEGER) && (sr1.sym->value != NULL))
					val = (int *)sr1.sym->value;
				else if((sr2.found == 1) && (sr2.sym->type == INTEGER) && (sr2.sym->value != NULL))
					val = (int *)sr2.sym->value;
				else err = 1;
				sym->size = *val;
				check_for_tok(CSQR_PAREN);
			}	
			else err = 1;
		}
		tok = next();
	}
	else if(tok == DECLR_ASIGN) // initilisation
	{
		check_valid_value(&sym);
		tok = next();
	}

	// checking if symbol is already present.
	sr1 = search(p.var_sym, name);
	sr2 = search(p.const_sym, name);
	err |= (sr1.found || sr2.found);

	if(err == 0)
	{
		// add symbol to appropiate table.
		if(c_v == 'v') p.var_sym = put(p.var_sym, sym);
		else if(c_v == 'c') p.const_sym = put(p.const_sym, sym);

		//validate next data item.
		if(tok == COMMA)
			check_data_item(c_v);
		else if(tok != SEMICOLON)
			err = 1;
	}
}

void check_declr()
{
	SearchResult sr;
	enum token tok = next();
	char str[32];
	if(tok == VAR)
		check_data_item('v');			
	else if (tok == CONST)
		check_data_item('c');
	else
		err = 1;
			
	tok = next();
	if(err == 0 && (tok == VAR || tok == CONST))
	{
		go_back();
		check_declr();
	}
}


_condition *parse_condition()
{
	enum token tok = next();
	_condition *c = NULL;
	_condition2 *c1;
	SearchResult sr;
	
	switch(tok)
	{
		case OROUND_PAREN:
			c = parse_condition();
			if(c == NULL) err = 1; // for () err handling
			else check_for_tok(CROUND_PAREN);
			break;

		case CROUND_PAREN:
			go_back();
			break;

		case NOT:
			c = create_condition((void *)parse_condition(), NOT_CONDITION);	
			break;

		case ID:
			sr = search(p.var_sym, cur_tok);
			if(sr.found == 0)
				sr = search(p.const_sym, cur_tok);

			if((sr.found == 1) && (sr.sym->type == BOOLEAN) && (sr.sym->value != NULL))
				c = create_condition((void *)sr.sym, ID_CONDITION);
			else err = 1;
			break;

		case TRUE:
			c = create_condition((void *)&__true, BOOL_VAL);
			break;

		case FALSE:
			c = create_condition((void *)&__false, BOOL_VAL);	
			break;

		default: err = 1;
	}	
	
	tok = next();
	if(tok == AND)
	{
		c1 = create_condition2(c, parse_condition());
		c = create_condition((void *)c1, AND_CONDITION);
	}
	else if(tok == OR)
	{
		c1 = create_condition2(c, parse_condition());
		c = create_condition((void *)c1, OR_CONDITION);
	}
	else go_back();
	return c;
}

void check_predicate(_guard **guard)
{
	enum token tok = next();
	_condition *c; 
	switch(tok)
	{
		case SEND:

			break;
		case RECV:

			break;
		case TIMEOUT:

			break;
		default:
			go_back();
			c = parse_condition();
	}
	(*guard)->predicate = c;
}

void check_event()
{

}

// for (key , val) in to_itr do
//        .... (instructions)
//  od
void check_forloop()
{
	SearchResult sr1, sr2, sr3;
	char key[32], val[32], to_itr[32];
	enum token tok;

	check_for_tok(FOR), check_for_tok(OROUND_PAREN);
	check_is_valid_id(); 	// cecking for valid key identifier
	strcpy(key, cur_tok);	// collecting key identifier
	
	check_for_tok(COMMA);
	check_is_valid_id();	// checking for valid val identifier 
	strcpy(val, cur_tok);   // collecting the val identifier

	check_for_tok(CROUND_PAREN), check_for_tok(IN);
	check_for_tok(ID);		// checking for valid array identifier
	strcpy(to_itr, cur_tok); 

}


void check_ifstmt()
{

}

void check_asign()
{

}

void check_action()
{
	enum token tok = next();

	go_back();
	switch(tok)
	{
		case SEND:
		case RECV:
		case TIMEOUT:
		case ACTIVATE:
			check_event();
			break;

		case FOR:
			check_forloop(); break;
		case IF:
			check_ifstmt(); break;
		case ID:
			check_asign(); break;
		default:
			err = 1;
	}
}

void check_guard()
{
	enum token tok = next();
	_guard *guard = create_guard(NULL, NULL);

	if(tok == GUARD)
	{
		check_predicate(&guard);
		if(next() == ACTION)
			check_action();
		else err = 1;

		if(next() == GUARD)
			check_guard();
		else go_back();
	}
	else err = 1;
}

void check_begin()
{
	if(next() == BEGIN)
		check_guard();
	else
		err = 1;

	if(next() != END) err = 1;
}	

int main()
{
	enum token tok;
	tokenizer_config();
	// print_tokens();return 0;
	p.var_sym = get_new_table(2);
	p.const_sym = get_new_table(2);

	check_commbox();
	tok = next();
	if(err == 0 && (tok == VAR || tok == CONST))
	{
		go_back();
		check_declr();

		if(err == 1) printf("Invalid declaration block.\n");
	}
	
	// go_back();
	// check_begin();
	printf("err :%d\n", err);
	return 0;
}

