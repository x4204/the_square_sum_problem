#include <stdio.h>
// ^^^~ for testing
#include <stdlib.h>
#include <math.h>
#include "graph.h"

static t_node *node_new(size_t value)
{
	t_node *elem;

	elem = (t_node *)malloc(sizeof(t_node));
	elem->value = value;
	elem->friendCount = 0;
	elem->friends = (t_node **)malloc(sizeof(t_node *) * DEF_FR_COUNT);
	return (elem);
}

static t_node **create_node_arr(size_t count)
{
	t_node **arr;

	arr = (t_node **)malloc(sizeof(t_node *) * count);
	for (size_t i = 0; i < count; i++)
		arr[i] = node_new(i + 1);
	return (arr);
}

static unsigned char is_perfect_square(size_t num)
{
	double res;
	size_t val;

	res = sqrt((double)num);
	return ((val = res) == res);
}

static void friends_handshake(t_node *friend1, t_node *friend2)
{
	friend1->friendCount++;
	friend2->friendCount++;
	if (friend1->friendCount > DEF_FR_COUNT)
		friend1->friends = (t_node **)realloc(friend1->friends, friend1->friendCount * sizeof(t_node));
	if (friend2->friendCount > DEF_FR_COUNT)
		friend2->friends = (t_node **)realloc(friend2->friends, friend2->friendCount * sizeof(t_node));
	friend1->friends[friend1->friendCount - 1] = friend2;
	friend2->friends[friend2->friendCount - 1] = friend1;
}

static void make_friends(t_node **arr, size_t count)
{
	for (size_t i = 0; i < count - 1; i++)
		for (size_t j = i + 1; j < count; j++)
			if (is_perfect_square(arr[i]->value + arr[j]->value))
				friends_handshake(arr[i], arr[j]);
}

static unsigned char all_nodes_are_visited(t_node **arr, size_t count)
{
	size_t visited_count = 0;

	for (size_t i = 0; i < count; i++)
		if (arr[i]->visited)
			visited_count++;
	return (visited_count == count);
}

static unsigned char all_friends_are_visited(t_node *elem)
{
	size_t visited_count = 0;

	for (size_t i = 0; i < elem->friendCount; i++)
		if (elem->friends[i]->visited)
			visited_count++;
	return (visited_count == elem->friendCount);
}

static void chain_push(t_chain **stk, size_t value)
{
	t_chain *elem;

	elem = (t_chain *)malloc(sizeof(t_chain));
	elem->value = value;
	elem->next = NULL;

	t_chain *head = *stk;
	if (!head)
		*stk = elem;
	else
	{
		while (head->next)
			head = head->next;
		head->next = elem;
	}
}

static void chain_pop(t_chain **stk)
{
	t_chain *current = *stk;

	if (!current)
		return ;
	if (!current->next)
	{
		*stk = NULL;
		free(current);
		return ;
	}
	while (current->next->next)
		current = current->next;
	free(current->next);
	current->next = NULL;
}

static void chain_copy(t_chain **dest, t_chain *src)
{
	while (src)
	{
		chain_push(dest, src->value);
		src = src->next;
	}
}

static int valid_chain(t_node **arr, size_t count, t_chain *stk, t_chain **sol, size_t index)
{
	chain_push(&stk, arr[index]->value);
	arr[index]->visited = 1;
	if (all_nodes_are_visited(arr, count))
	{
  	chain_copy(sol, stk);
		return (1);
	}
	if (arr[index]->friendCount == 0 || all_friends_are_visited(arr[index]))
	{
		chain_pop(&stk);
		arr[index]->visited = 0;
		return (0);
	}
	for (size_t i = 0; i < arr[index]->friendCount; i++)
		if (!arr[index]->friends[i]->visited)
			if (valid_chain(arr, count, stk, sol, arr[index]->friends[i]->value - 1))
				return (1);
	chain_pop(&stk);
	arr[index]->visited = 0;
	return (0);
}

void print_chain(t_chain *stk)
{
	if (!stk)
	{
		printf("Empty chain\n");
		return ;
	}
	while (stk)
	{
		printf("%lu ", stk->value);
		stk = stk->next;
	}
	printf("\n");
}

t_chain	*create_chain(size_t count)
{
	t_node **arr;
	t_chain *stk = NULL;
	t_chain *sol = NULL;

	arr = create_node_arr(count);
	make_friends(arr, count);
	// ptarr(arr, count); // debug
	for (size_t i = 0; i < count; i++)
		if (valid_chain(arr, count, stk, &sol, i))
			return (sol);
	return (NULL);
}















// tactical dot (.)
