#include "instruction.h"
#include "condition.h"


#ifndef GUARD_H
#define GUARD_H

typedef struct _guard _guard;

struct _guard
{
	_condition *predicate;
	_instruction *statement;
	void destroy(struct _guard*); 
};

_guard *create_guard(_condition *predicate, _instruction *statement);
void destroy_guard(_guard *guard);

#endif
