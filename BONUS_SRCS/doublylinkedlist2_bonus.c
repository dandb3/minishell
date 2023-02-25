/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublylinkedlist2_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:10:57 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/25 13:03:43 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	insert_node(t_node *insert_point, t_node *node)
{
	insert_point->next->prev = node;
	node->next = insert_point->next;
	node->prev = insert_point;
	insert_point->next = node;
}

void	sort_list(t_list *list)
{
	t_node	*cur1;
	t_node	*cur2;
	t_env	*tmp;

	cur1 = list->head->next;
	while (cur1->next)
	{
		cur2 = cur1->next;
		while (cur2->next)
		{
			if (ft_strcmp(cur1->val, cur2->val) > 0)
			{
				tmp = cur1->val;
				cur1->val = cur2->val;
				cur2->val = tmp;
			}
			cur2 = cur2->next;
		}
		cur1 = cur1->next;
	}
}

t_node	*make_node(void *val, t_lex lex)
{
	t_node	*result;

	if (val == NULL)
		return (NULL);
	result = (t_node *) malloc(sizeof(t_node));
	if (result == NULL)
		exit(MALLOC_FAILURE);
	ft_memset(result, 0, sizeof(t_node));
	result->val = val;
	result->lex = lex;
	return (result);
}

void	free_node(t_node *node, t_type type)
{
	if (type == ENV)
	{
		free(((t_env *)(node->val))->val);
		free(((t_env *)(node->val))->key);
	}
	if (node->lex == LEX_COMPOUND)
		free_list(node->val, 0, LEX);
	else
		free(node->val);
	free(node);
}

int	get_list_length(t_list *list)
{
	t_node	*cur;
	int		len;

	cur = list->head;
	if (list->type == ENV)
		cur = cur->next;
	len = 0;
	while (cur->next)
	{
		++len;
		cur = cur->next;
	}
	return (len);
}
