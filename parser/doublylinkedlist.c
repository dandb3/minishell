/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublylinkedlist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:11:49 by jdoh              #+#    #+#             */
/*   Updated: 2023/01/24 18:51:30 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_lst	*make_list(void)
{
	t_lst	*result;

	result = (t_lst *) malloc(sizeof(t_lst));
	if (result == NULL)
		return (NULL);
	result->head = make_token(ft_strdup(""), -1);
	result->tail = make_token(ft_strdup(""), -1);
	result->size = 0;
	if (result->head == NULL || result->tail == NULL)
		return ((t_lst *)free_ret(result->head, result->tail, result, 0));
	result->head->next = result->tail;
	result->tail->prev = result->head;
	return (result);
}

void	del_token(t_token *token)
{
	token->prev->next = token->next;
	token->next->prev = token->prev;
	free_token(token);
}

void	push_token(t_token *token, t_lst *list)
{
	list->tail->prev->next = token;
	token->prev = list->tail->prev;
	token->next = list->tail;
	list->tail->prev = token;
	++(list->size);
}

long long	free_tokens(t_lst *list, long long ret)
{
	t_token	*cur_token;
	t_token	*del_token;

	cur_token = list->head->next;
	while (cur_token->next != NULL)
	{
		del_token = cur_token;
		cur_token = cur_token->next;
		free_token(del_token);
	}
	list->head->next = list->tail;
	list->tail->prev = list->head;
	return (ret);
}

long long	free_list(t_lst *list, long long ret)
{
	free_tokens(list, 0);
	free_token(list->head);
	free_token(list->tail);
	free(list);
	return (ret);
}
