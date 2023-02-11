/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_unused.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:15:55 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/11 23:02:02 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	del_quotes(t_list *token_list)
{
	t_node	*cur_token;

	cur_token = token_list->head->next;
	while (cur_token->next != NULL)
	{
		if (cur_token->lex == LEX_DOUBLE_QUOTE \
			|| cur_token->lex == LEX_SINGLE_QUOTE)
		{
			free(cur_token->val);
			cur_token->lex = LEX_WORD;
			cur_token->val = ft_strdup("");
			if (cur_token->val == NULL)
				exit(MALLOC_FAILURE);
		}
		cur_token = cur_token->next;
	}
}

void	del_whitespace(t_list *token_list)
{
	t_node	*cur_token;

	cur_token = token_list->head->next;
	while (cur_token->next != NULL)
	{
		if (cur_token->lex == LEX_WHITE)
		{
			cur_token = cur_token->prev;
			del_node(cur_token->next, LEX);
		}
		cur_token = cur_token->next;
	}
}
