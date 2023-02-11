#include "parser.h"

void	pop(t_list *stack)
{
	t_node	*popped;

	popped = stack->head->next;
	popped->prev->next = popped->next;
	popped->next->prev = popped->prev;
	free(popped);
	--(stack->size);
}

void	push(t_list *stack, t_tree *tree_node)
{
	t_node	*new_node;

	new_node = (t_node *) malloc(sizeof(t_node));
	if (new_node == NULL)
		exit(MALLOC_FAILURE);
	new_node->val = tree_node;
	new_node->prev = stack->head;
	new_node->next = stack->head->next;
	new_node->next->prev = new_node;
	new_node->prev->next = new_node;
	++(stack->size);
}

t_node	*top(t_list *stack)
{
	return (stack->head->next);
}

int	stack_empty(t_list *stack)
{
	if (stack->size == 0)
		return (1);
	return (0);
}
