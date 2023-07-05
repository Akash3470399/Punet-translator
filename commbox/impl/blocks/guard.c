#include <stdlib.h>

#include "../../intr/blocks/guard.h"


_guard *create_guard(_condition *predicate, _instruction *statement)
{
	_guard *new_guard = (_guard *)malloc(sizeof(_guard));
	new_guard->predicate = predicate;
	new_guard->statement = statement;
	//new_guard->destroy = destroy_guard;
	return new_guard;
}

/*void destroy_guard(_guard *guard)
{
	(guard->predicate)->destroy(guard->predicate);
	(guard->statement)->destroy(guard->statement);
	free(guard);
}*/
