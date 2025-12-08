#include "vbcc.h"

t_node	*new_node(t_node n)
{
	t_node	*ret_node;

	ret_node = calloc(1, sizeof(n));
	if (!ret_node)
		return (NULL);
	*ret_node = n;
	return (ret_node);
}

void	destroy_tree(t_node *n)
{
	if (!n)
		return ;
	if (n->type != VAL)
	{
		destroy_tree(n->l);
		destroy_tree(n->r);
	}
	free(n);
}

void	unexpected(char c)
{
	if (c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of input\n");
}

t_node	*parse_expr(char **s)
{
	t_node	*left = parse_term(s);
	if (!left)
		return (NULL);
	while (**s && **s == '+')
	{
		(*s)++;
		t_node	*right = parse_term(s);
		if (!right)
		{
			destroy_tree(left);
			return (NULL);
		}
		t_node	n = {ADD, 0, left, right};
		left = new_node(n);
		if (!left)
		{
			destroy_tree(right);
			return (NULL);
		}
	}
	return (left);
}

t_node	*parse_term(char **s)
{
	t_node	*left = parse_fact(s);
	if (!left)
		return (NULL);
	while (**s && **s == '*')
	{
		(*s)++;
		t_node	*right = parse_fact(s);
		if (!right)
		{
			destroy_tree(left);
			return (NULL);
		}
		t_node	n = {MULT, 0, left, right};
		left = new_node(n);
		if (!left)
		{
			destroy_tree(right);
			return (NULL);
		}
	}
	return (left);
}

t_node	*parse_fact(char **s)
{
	if (isdigit(**s))
	{
		t_node	n = {VAL, **s - '0', NULL, NULL};
		(*s)++;
		return (new_node(n));
	}
	if (**s && **s == '(')
	{
		(*s)++;
		t_node	*node = parse_expr(s);
		if (**s && **s != ')')
		{
			unexpected(**s);
			return (NULL);
		}
		(*s)++;
		return (node);
	}
	unexpected(**s);
	return (NULL);
}

int	valid_tree(t_node *tree)
{
	if (tree->type == ADD)
		return (valid_tree(tree->l) + valid_tree(tree->r));
	else if (tree->type == MULT)
		return (valid_tree(tree->l) * valid_tree(tree->r));
	else
		return (tree->val);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	t_node	*tree = parse_expr(&av[1]);
	if (!tree || *av[1])
	{
		if (*av[1] && tree)
			unexpected(*av[1]);
		//else if (!tree)
		//	unexpected(0);
		return (1);
	}
	printf("%d\n", valid_tree(tree));
	destroy_tree(tree);
}
