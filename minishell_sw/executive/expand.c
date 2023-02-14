/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:46:23 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/14 21:32:38 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	expand_env(t_node *env_token)
{
	char	*val;

	val = find_env_val(env_token->val);
	free(env_token->val);
	env_token->val = val;
}

static void	expand_wild(t_node *env_token)
{
	(void) env_token
}

static void	merge_two_words(t_node *prev_token, t_node *cur_token)
{
	char	*merged_word;

	if (cur_token->val == NULL)
		return ;
	merged_word = ft_strjoin(prev_token->val, cur_token->val);
	if (merged_word == NULL)
		exit(MALLOC_FAILURE);
	free(cur_token->val);
	cur_token->val = merged_word;
	del_node(prev_token, LEX);
}

char	*expand_char(t_list *compound_list)
{
	t_node	*first_token;
	t_node	*cur_token;
	char	*ret;

	first_token = compound_list->head->next;
	cur_token = first_token;
	while (cur_token->next != NULL)
	{
		if (cur_token->lex == LEX_ENV)
			expand_env(cur_token);
		if (cur_token->lex == LEX_WILD)
			first_token->lex = LEX_WILD;
		if (cur_token->prev->lex != -1)
			merge_two_words(cur_token->prev, cur_token);
		cur_token = cur_token->next;
	}
	if (first_token->lex == LEX_WILD)
		expand_wild(first_token);
	ret = first_token->val;
	first_token->val = NULL;
	return (ret);
}
