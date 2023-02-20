/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublylinkedlist3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:28:12 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/20 13:25:55 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*copy_list(t_list *list)
{
	t_list	*new_list;
	t_node	*cur_token;

	if (list->type != COMPOUND)
		return (NULL);
	new_list = make_list(COMPOUND);
	cur_token = list->head->next;
	while (cur_token->next != NULL)
	{
		push_node(make_node(copy_val(cur_token), cur_token->lex), new_list);
		cur_token = cur_token->next;
	}
	return (new_list);
}

void	*copy_val(t_node *node)
{
	void	*ret;

	ret = ft_strdup(node->val);
	if (ret == NULL)
		exit(MALLOC_FAILURE);
	return (ret);
}

t_node	*make_null_value_node(t_lex lex)
{
	t_node	*result;

	result = (t_node *)ft_calloc(1, sizeof(t_node));
	if (result == NULL)
		exit(MALLOC_FAILURE);
	result->lex = lex;
	return (result);
}
