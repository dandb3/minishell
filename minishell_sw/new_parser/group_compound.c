/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_compound.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 19:57:08 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/11 23:02:05 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_node	*compound_end(t_node *end_token)
{
	while (end_token->next != NULL)
	{
		if (end_token->lex != LEX_WORD && end_token->lex != LEX_WILD \
			&& end_token->lex != LEX_ENV)
			break ;
		end_token = end_token->next;
	}
	return (end_token->prev);
}

void	group_compound(t_list *token_list)
{
	t_node	*cur_token;
	t_node	*end_token;
	t_node	*new_token;

	cur_token = token_list->head->next;
	while (cur_token->next != NULL)
	{
		if (cur_token->lex == LEX_WORD || cur_token->lex == LEX_WILD \
			|| cur_token->lex == LEX_ENV)
		{
			new_token = make_node(make_list(LEX), LEX_COMPOUND);
			end_token = compound_end(cur_token);
			cur_token->prev->next = new_token;
			new_token->prev = cur_token->prev;
			new_token->next = end_token->next;
			end_token->next->prev = new_token;
			cur_token->prev = ((t_list *)(new_token->val))->head;
			((t_list *)(new_token->val))->head->next = cur_token;
			end_token->next = ((t_list *)(new_token->val))->tail;
			((t_list *)(new_token->val))->tail->prev = end_token;
			cur_token = new_token;
		}
		cur_token = cur_token->next;
	}
}
