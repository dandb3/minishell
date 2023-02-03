/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:40:54 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/03 20:37:05 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	merge_two_words(t_node *w1, t_node *w2)
{
	char	*merged_word;

	merged_word = ft_strjoin(w1->val, w2->val);
	if (merged_word == NULL)
		exit(MALLOC_FAILURE);
	free(w1->val);
	w1->val = merged_word;
	if (w1->lex == LEX_WILD || w2->lex == LEX_WILD)
		w1->lex = LEX_WILD;
	else
		w1->lex = LEX_WORD;
	del_node(w2, LEX);
}

void	merge_words(t_list *token_list)
{
	t_node	*cur_token;

	cur_token = token_list->head->next;
	while (cur_token->next != NULL)
	{
		if ((cur_token->lex == LEX_WILD || cur_token->lex == LEX_WORD)
			&& (cur_token->prev->lex == LEX_WILD
				|| cur_token->prev->lex == LEX_WORD))
		{
			cur_token = cur_token->prev;
			merge_two_words(cur_token, cur_token->next);
		}
		cur_token = cur_token->next;
	}
}

int	del_white_tokens(t_list *token_list)
{
	t_node	*cur_token;
	int		parenthesis_cnt;

	parenthesis_cnt = 0;
	cur_token = token_list->head->next;
	while (cur_token->next != NULL)
	{
		if (cur_token->lex == LEX_PARENTHESIS_OPEN)
			++parenthesis_cnt;
		if (cur_token->lex == LEX_PARENTHESIS_CLOSE && --parenthesis_cnt < 0)
			return (FAILURE);
		if (cur_token->lex == LEX_WHITE)
		{
			cur_token = cur_token->prev;
			del_node(cur_token->next, LEX);
		}
		cur_token = cur_token->next;
	}
	if (parenthesis_cnt != 0)
		return (FAILURE);
	return (SUCCESS);
}
