#include <stdio.h>
#include <stdlib.h>
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

static unsigned char all_friends_are_visited(t_node *elem)
{
	size_t visited_count = 0;

	for (size_t i = 0; i < elem->friendCount; i++)
		if (elem->friends[i]->visited)
			visited_count++;
	return (visited_count == elem->friendCount);
}

static t_stack *stack_alloc(size_t count)
{
	t_stack *ret;

	ret = (t_stack *)malloc(sizeof(t_stack));
	ret->nodes = (t_node **)malloc(sizeof(t_node *) * count);
	ret->len = 0;
	return (ret);
}

static void stack_push(t_stack *stk, t_node *node)
{
	stk->nodes[stk->len] = node;
	stk->len++;
}

static void stack_pop(t_stack *stk)
{
	if (stk->len > 0)
		stk->len--;
}

static void stack_copy(t_stack **dest, t_stack *src)
{
	for (size_t i = 0; i < src->len; i++)
		stack_push(*dest, src->nodes[i]);
}

static int valid_chain(t_node **arr, size_t count, t_stack *stk, t_stack **sol, size_t index)
{
	stack_push(stk, arr[index]);
	arr[index]->visited = 1;
	if (stk->len == count)
	{
  	stack_copy(sol, stk);
		return (1);
	}
	if (arr[index]->friendCount == 0 || all_friends_are_visited(arr[index]))
	{
		stack_pop(stk);
		arr[index]->visited = 0;
		return (0);
	}
	for (size_t i = 0; i < arr[index]->friendCount; i++)
		if (!arr[index]->friends[i]->visited)
			if (valid_chain(arr, count, stk, sol, arr[index]->friends[i]->value - 1))
				return (1);
	stack_pop(stk);
	arr[index]->visited = 0;
	return (0);
}

void print_stack(t_stack *stk)
{
	if (stk->len == 0)
	{
		printf("Empty stack\n");
		return ;
	}
	for (size_t i = 0; i < stk->len; i++)
		printf("%u ", stk->nodes[i]->value);
	printf("\n");
	(void)stk;
}

// for debug
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

t_stack	*create_chain(size_t count)
{
	t_node **arr;
	t_stack *stk;
	t_stack *sol;

	arr = create_node_arr(count);
	stk = stack_alloc(count);
	sol = stack_alloc(count);
	make_friends(arr, count);
	// ptarr(arr, count); // debug
	for (size_t i = 0; i < count; i++)
		if (valid_chain(arr, count, stk, &sol, i))
			return (sol);
	return (NULL);
}















// tactical dot (.)
