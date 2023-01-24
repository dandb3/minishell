/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_tokenizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:37:47 by jdoh              #+#    #+#             */
/*   Updated: 2023/01/24 17:35:34 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static size_t	whitespace_len(char const *str)
{
	size_t	idx;

	idx = 0;
	while (str[idx] == ' ' || str[idx] == '\t')
		idx++;
	return (idx);
}

static size_t	word_len(char const *str)
{
	size_t	idx;

	idx = 0;
	while (!ft_strchr("|<>\'\"$* \t", str[idx]) && ft_strncmp(&str[idx], "&&", 2)
		&& str[idx])
		idx++;
	return (idx);
}

static char	*get_lexeme(char const **str, size_t len)
{
	char	*result;

	result = ft_substr(*str, 0, len);
	(*str) += len;
	return (result);
}

static t_token	*get_token(char const **str)
{
	if (!ft_strncmp(*str, "&&", 2))
		return (make_token(get_lexeme(str, 2), LEX_AND));
	if (!ft_strncmp(*str, ">>", 2))
		return (make_token(get_lexeme(str, 2), LEX_REDIRECT_APP));
	if (!ft_strncmp(*str, "<<", 2))
		return (make_token(get_lexeme(str, 2), LEX_HERE_DOC));
	if (!ft_strncmp(*str, "||", 2))
		return (make_token(get_lexeme(str, 2), LEX_OR));
	if (!ft_strncmp(*str, "\'", 1))
		return (make_token(get_lexeme(str, 1), LEX_SINGLE_QUOTE));
	if (!ft_strncmp(*str, "\"", 1))
		return (make_token(get_lexeme(str, 1), LEX_DOUBLE_QUOTE));
	if (!ft_strncmp(*str, "<", 1))
		return (make_token(get_lexeme(str, 1), LEX_REDIRECT_IN));
	if (!ft_strncmp(*str, ">", 1))
		return (make_token(get_lexeme(str, 1), LEX_REDIRECT_OUT));
	if (!ft_strncmp(*str, "|", 1))
		return (make_token(get_lexeme(str, 1), LEX_PIPE));
	if (!ft_strncmp(*str, "$", 1))
		return (make_token(get_lexeme(str, 1), LEX_ENV));
	if (!ft_strncmp(*str, "*", 1))
		return (make_token(get_lexeme(str, 1), LEX_WILD));
	if (**str == ' ' || **str == '\t')
		return (make_token(get_lexeme(str, whitespace_len(*str)), LEX_WHITE));
	return (make_token(get_lexeme(str, word_len(*str)), LEX_WORD));
}

t_lst	*make_token_list(char const *str)
{
	t_lst		*result;
	t_token		*new_token;

	result = make_list();
	if (result == NULL)
		return (NULL);
	while (*str)
	{
		new_token = get_token(&str);
		if (new_token == NULL)
			return ((t_lst *)free_list(result, 0));
		push_token(new_token, result);
	}
	return (result);
}
