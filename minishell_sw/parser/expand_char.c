/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:40:44 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/03 20:35:39 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*find_env_val(t_list *env_list, char const *key)
{
	t_node	*cur_env;
	char	*ret;

	cur_env = env_list->head->next;
	while (cur_env->next != NULL)
	{
		if (!ft_strcmp(((t_env *)(cur_env->val))->key, key))
		{
			ret = ft_strdup(((t_env *)(cur_env->val))->val);
			if (ret == NULL)
				exit(MALLOC_FAILURE);
			return (ret);
		}
		cur_env = cur_env->next;
	}
	ret = ft_strdup("");
	if (ret == NULL)
		exit(MALLOC_FAILURE);
	return (ret);
}

static void	substitute_env(t_node *cur_token, t_list *env_list, t_flag flag)
{
	cur_token->lex = LEX_WORD;
	if (cur_token->next->next == NULL)
		return ;
	if (flag == UN_QUOTED && (cur_token->next->lex == LEX_SINGLE_QUOTE
			|| cur_token->next->lex == LEX_DOUBLE_QUOTE))
		del_node(cur_token, LEX);
	else if (cur_token->next->lex == LEX_WORD)
	{
		free(cur_token->val);
		cur_token->val = find_env_val(env_list, cur_token->next->val);
		del_node(cur_token->next, LEX);
	}
}

int	expand_env(t_list *token_list, t_list *env_list)
{
	t_node	*cur_token;
	t_flag	flag;

	flag = UN_QUOTED;
	cur_token = token_list->head->next;
	while (cur_token->next != NULL)
	{
		if (flag == UN_QUOTED && cur_token->lex == LEX_SINGLE_QUOTE)
			flag = SINGLE_QUOTED;
		else if (flag == UN_QUOTED && cur_token->lex == LEX_DOUBLE_QUOTE)
			flag = DOUBLE_QUOTED;
		else if ((flag == SINGLE_QUOTED && cur_token->lex == LEX_SINGLE_QUOTE)
			|| (flag == DOUBLE_QUOTED && cur_token->lex == LEX_DOUBLE_QUOTE))
			flag = UN_QUOTED;
		else if ((flag == UN_QUOTED || flag == DOUBLE_QUOTED)
			&& cur_token->lex == LEX_ENV)
			substitute_env(cur_token, env_list, flag);
		cur_token = cur_token->next;
	}
	if (flag != UN_QUOTED)
		return (FAILURE);
	return (SUCCESS);
}

static void	substitute_quotes(t_node *cur_token, t_lex quote)
{
	t_node	*merged_token;

	cur_token->lex = LEX_WORD;
	free(cur_token->val);
	cur_token->val = ft_strdup("");
	if (cur_token->val == NULL)
		exit(MALLOC_FAILURE);
	cur_token = cur_token->next;
	while (cur_token->lex != quote)
	{
		merged_token = cur_token;
		merged_token->lex = LEX_WORD;
		cur_token = cur_token->next;
		merge_two_words(merged_token->prev, merged_token);
	}
	del_node(cur_token, LEX);
}

void	expand_quotes(t_list *token_list)
{
	t_node	*cur_token;

	cur_token = token_list->head->next;
	while (cur_token->next != NULL)
	{
		if (cur_token->lex == LEX_SINGLE_QUOTE \
			|| cur_token->lex == LEX_DOUBLE_QUOTE)
			substitute_quotes(cur_token, cur_token->lex);
		cur_token = cur_token->next;
	}
}
