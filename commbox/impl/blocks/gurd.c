#include <stdlib.h>

#include "../../intr/blocs/guard.h"


_guard *create_guard(_condition *predicate, _instruction *statement)
{
	_guard *new_guard = (_guard *)malloc(sizeof(_guard));
	new_guard->predicate = predicate;
	new_guard->statement = statement;
	new_guard->destroy = destroy_guard;
	return new_guard;
}

void destroy_guard(_guard *guard)
{
	new_guard->predicate->destroy(new_guard->predicate);
	new_guard->statement->destroy(new_guard->statement);
	free(guard);
}
