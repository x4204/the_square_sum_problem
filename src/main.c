#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void checkArgs(int ac, char *av1)
{
	if (ac != 2)
	{
		printf("usage: ./square_sum <upper_limit as integer>\n");
		exit(1);
	}
	if (atoi(av1) <= 0)
	{
		printf("The upper limit should be a positive number > 0\n");
		exit(1);
	}
}

int main(int argc, char **argv)
{
	checkArgs(argc, argv[1]);
	// ---------------------------------------------------------------------------
	int count = atoi(argv[1]);
	t_stack *sol = create_chain(count);

	if (!sol)
		printf("There is no way to arrange the numbers\n");
	else
	{
		printf("The solution is:\n");
		print_stack(sol);
	}
	return (0);
}
