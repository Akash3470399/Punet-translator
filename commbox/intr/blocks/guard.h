#include "instruction.h"
#include "condition.h"


#ifndef GUARD_H
#define GUARD_H

typedef struct _guard _guard;

struct _guard
{
	_condition *predicate;
	_instruction *statement;
};


#endif
