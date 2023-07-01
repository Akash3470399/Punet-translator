#include <stdio.h>
#include <stdlib.h>

int main()
{

	int *b = malloc(sizeof(int));
	*b = 4;
	void *a = (void *)b;
	int *c = (int *)a;
	printf("%d", *c);
	return 0;
}
