# ifndef VBCC_H
# define VBCC_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct s_node
{
	enum
	{
		ADD,
		MULT,
		VAL
	}	type;
	int	val;
	struct s_node	*l;
	struct s_node	*r;
}				t_node;

t_node	*parse_expr(char **s);
t_node	*parse_term(char **s);
t_node	*parse_fact(char **s);

# endif