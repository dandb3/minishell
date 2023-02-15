/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:46:23 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/15 20:14:15 by sunwsong         ###   ########.fr       */
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

static void	expand_wild(t_node *token)
{
	char	*wstr;

	wstr = wildcard((char *)(token->val));
	free(token->val);
	token->val = wstr;
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

static void	replace_asterisk(t_node *cur_token, size_t wlen, int *is_wild)
{
	const size_t	len = ft_strlen(cur_token->val);
	size_t			idx;
	char			*val;

	*is_wild = TRUE;
	val = (char *)(cur_token->val);
	idx = len - wlen;
	while (idx < len)
	{
		if (val[idx] == '*')
			val[idx] = 0;
		++idx;
	}
}

char	*expand_char(t_list *compound_list)
{
	t_node	*cur_token;
	size_t	len;
	char	*ret;
	int		is_wild;

	is_wild = FALSE;
	cur_token = compound_list->head->next;
	del_quotes(compound_list);
	while (cur_token->next != NULL)
	{
		if (cur_token->lex == LEX_ENV)
			expand_env(cur_token);
		if (cur_token->lex == LEX_WILD)
			len = ft_strlen(cur_token->val);
		if (cur_token->prev->lex != -1)
			merge_two_words(cur_token->prev, cur_token);
		if (cur_token->lex == LEX_WILD)
			replace_asterisk(cur_token, len, &is_wild);
		cur_token = cur_token->next;
	}
	if (is_wild == TRUE)
		expand_wild(compound_list->head->next->val);
	ret = compound_list->head->next->val;
	compound_list->head->next->val = NULL;
	return (ret);
}
