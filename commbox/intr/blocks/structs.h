#ifndef STRUCTS_H
#define STRUCTS_H


enum ins_type {GUARD_INS, EVENT_INS, CONTROL_INS};
enum condition_type {NOT_CONDITION, AND_CONDITION, OR_CONDITION, ID_CONDITION, BOOL_VAL};
enum event_type {SEND_EVENT, RECV_EVENT, ACTIVATE_EVENT, TIMEOUT_EVENT};

typedef struct _instruction _instruction;
typedef struct _guard _guard;

typedef struct _condition1 _condition1;
typedef struct _condition2 _condition2;
typedef struct _condition _condition;

typedef struct _event_ins _event_ins;
typedef struct _control_ins _control_ins;

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
		int (*eval)(struct _condition *);
	}c;
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
		_guard *guard;
		_event_ins *event;
		_control_ins *control_stmt;		
	}s; // statement
	    //
	void (*destroy)(struct _instruction *);
};


struct _event_ins
{

};

struct _control_ins
{

};

#endif
