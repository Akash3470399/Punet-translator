#include "guard.h"
#include "event.h"
#include "control_stmt.h"


#ifndef INSTRUCTION_H
#define INSTRUCTION_H

enum ins_type {GUARD_INS, EVENT_INS, CONTROL_INS};
typedef struct _instruction _instruction;

struct _instruction
{
	enum ins_type type;
	union{
		_guard *guard;
		_event_ins *event;
		_control_ins *control_stmt;		
	}s; // statement
};

#endif
