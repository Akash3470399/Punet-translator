#include "instruction.h"
#include "structs.h"
#include "condition.h"


#ifndef GUARD_H
#define GUARD_H
_guard *create_guard(_condition *predicate, _instruction *statement);
void destroy_guard(_guard *guard);

#endif
