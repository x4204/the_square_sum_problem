#ifndef GRAPH_H
# define GRAPH_H

# include <math.h>

# define DEF_FR_COUNT 5							// default friend count

typedef struct		s_node
{
	size_t					value 			: 12;	// max value = 4096
	size_t					friendCount : 11;	// max friend count = 2048
	unsigned char		visited 		: 1;	// either 1 or 0
	struct s_node		**friends;
}									t_node;

typedef struct		s_chain
{
	size_t					value;
	struct s_chain	*next;
}									t_chain;

t_chain	*create_chain(size_t count);
void		print_chain(t_chain *stk);

#endif
