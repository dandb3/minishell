/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublylinkedlist1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:11:49 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/18 13:15:42 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*make_list(t_type type)
{
	t_list	*result;

	result = (t_list *) malloc(sizeof(t_list));
	if (result == NULL)
		exit(MALLOC_FAILURE);
	if (type == ENV)
	{
		result->head = make_node(make_env("", FALSE), -1);
		result->tail = make_node(make_env("z", FALSE), -1);
		*(((t_env *)(result->tail->val))->key) = '\177';
	}
	else
	{
		result->head = make_node(ft_strdup(""), -1);
		result->tail = make_node(ft_strdup(""), -1);
	}
	result->size = 0;
	if (result->head == NULL || result->tail == NULL)
		exit(MALLOC_FAILURE);
	result->head->next = result->tail;
	result->tail->prev = result->head;
	result->type = type;
	return (result);
}

void	del_node(t_node *node, t_type type)
{
	node->prev->next = node->next;
	node->next->prev = node->prev;
	free_node(node, type);
}

void	push_node(t_node *node, t_list *list)
{
	list->tail->prev->next = node;
	node->prev = list->tail->prev;
	node->next = list->tail;
	list->tail->prev = node;
	++(list->size);
}

long long	free_nodes(t_list *list, long long ret, t_type type)
{
	t_node	*cur_node;
	t_node	*del_node;

	cur_node = list->head->next;
	while (cur_node->next != NULL)
	{
		del_node = cur_node;
		cur_node = cur_node->next;
		free_node(del_node, type);
	}
	list->head->next = list->tail;
	list->tail->prev = list->head;
	return (ret);
}

long long	free_list(t_list *list, long long ret, t_type type)
{
	if (!list)
		return (ret);
	free_nodes(list, 0, type);
	free_node(list->head, type);
	free_node(list->tail, type);
	free(list);
	return (ret);
}
