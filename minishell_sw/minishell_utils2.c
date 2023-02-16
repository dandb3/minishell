/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:24:55 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/14 21:05:56 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_to_word(t_node *env_token)
{
	char	*tmp;

	env_token->lex = LEX_WORD;
	tmp = ft_strjoin("$", env_token->val);
	if (!tmp)
		exit(MALLOC_FAILURE);
	free(env_token->val);
	env_token->val = tmp;
}

static void	merge_two_words(t_node *prev_token, t_node *cur_token)
{
	char	*merged_word;

	merged_word = ft_strjoin(prev_token->val, cur_token->val);
	if (merged_word == NULL)
		exit(MALLOC_FAILURE);
	free(cur_token->val);
	cur_token->val = merged_word;
	del_node(prev_token, LEX);
}

char	*extract_pure_word(t_list *compound_list)
{
	t_node	*cur_token;
	char	*ret;

	cur_token = compound_list->head->next;
	while (cur_token->next != NULL)
	{
		if (cur_token->lex == LEX_ENV)
			env_to_word(cur_token);
		if (cur_token->prev->lex != -1)
			merge_two_words(cur_token->prev, cur_token);
		cur_token = cur_token->next;
	}
	ret = compound_list->head->next->val;
	compound_list->head->next->val = NULL;
	return (ret);
}
