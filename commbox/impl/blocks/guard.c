#include <stdlib.h>

#include "../../intr/blocks/guard.h"


_guard *create_guard(_condition *predicate, _instruction *ins_head)
{
	_guard *new_guard = (_guard *)malloc(sizeof(_guard));
	new_guard->predicate = predicate;
	new_guard->ins_head = ins_head;

	//new_guard->destroy = destroy_guard;
	return new_guard;
}

/*void destroy_guard()
{
	(guard->predicate)->destroy(guard->predicate);
	(guard->statement)->destroy(guard->statement);
	free(guard);
}*/
