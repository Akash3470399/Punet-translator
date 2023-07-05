#include "instruction.h"
#include "condition.h"
#include "structs.h"


#ifndef GUARD_H
#define GUARD_H
_guard *create_guard(_condition *predicate, _instruction *statement);
//void destroy_guard(_guard *guard);

#endif
