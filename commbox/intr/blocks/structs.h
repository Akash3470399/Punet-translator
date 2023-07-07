#ifndef STRUCTS_H
#define STRUCTS_H


enum ins_type {SEND_EVENT_INS, RECV_EVENT_INS, ACIVATE_EVENT_INS, TIMEOUT_EVENT_INS, IF_INS, FOR_INS, ASIGN_INS};

enum condition_type {NOT_CONDITION, AND_CONDITION, OR_CONDITION, ID_CONDITION, BOOL_VAL};

typedef struct _condition _condition;
typedef struct _condition2 _condition2;

typedef struct _guard _guard;

typedef struct _instruction _instruction;

typedef struct _forinloop_ins _forinloop_ins;
typedef struct _ifthen_ins _ifthen_ins;


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
};

struct _condition2
{
	_condition *c1;
	_condition *c2;
};

struct _condition 
{
	enum condition_type type;
	union conditon{
		_condition *c;
		_condition2 *c2;
		struct symbol *s;
		int *bool_val;

		// eval method
	}c;
	int (*eval)(struct _condition *);
	void (*destroy)(); 
};


struct _guard
{
	_condition *predicate;
	_instruction *statement;
	//void (*destroy)(struct _guard*); 
};


struct _instruction
{
	enum ins_type type;
	union{
		// events
		_forinloop_ins *forinloop;	
		_ifthen_ins *ifthenstmt;
	}s; // statement
	struct _instruction *next;
	void (*destroy)(struct _instruction *);
};




//********** INSTRUCTIONS ***********
struct _forinloop_ins
{
	struct symbol *key, *val, *to_itr;
	struct _instruction *ins_head;
	
	void (*execute)(struct _forinloop_ins *);
	void (*destroy)(struct _forinloop_ins *);
};


struct _ifthen_ins
{
	_condition *predicate;
	struct _instruction *ins_head;

	void (*execute)(struct _ifthen_ins *);
	void (*destroy)(struct _ifthen_ins *);
};

#endif
