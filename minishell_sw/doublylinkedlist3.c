/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublylinkedlist3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:28:12 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/12 12:34:45 by jdoh             ###   ########seoul.kr  */
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
		push_node(make_node(cur_token->val, cur_token->lex), new_list);
		cur_token = cur_token->next;
	}
}
