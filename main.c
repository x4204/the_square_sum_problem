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

void ptarr(t_node **arr, size_t count)
{
	for (size_t i = 0; i < count; i++)
	{
		printf("---------------------------\n");
		printf("[%lu]\n", i);
		printf("\tValue: %u\n", arr[i]->value);
		printf("\tFriend Count: %u\n", arr[i]->friendCount);
		printf("\tFriends: ");
		for (size_t j = 0; j < arr[i]->friendCount; j++)
			printf("%u ", arr[i]->friends[j]->value);
		printf("\n---------------------------\n");
	}
}

int main(int argc, char **argv)
{
	checkArgs(argc, argv[1]);
	// ---------------------------------------------------------------------------
	int count = atoi(argv[1]);
	t_chain *sol = create_chain(count);

	if (!sol)
		printf("There is no way to arrange the numbers\n");
	else
	{
		printf("The solution is:\n");
		print_chain(sol);
	}
	return (0);
}
