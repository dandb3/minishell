/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_nodeizer1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:37:47 by jdoh              #+#    #+#             */
/*   Updated: 2023/01/27 09:56:00 by sunwsong         ###   ########.fr       */
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
	while (!ft_strchr("|<>\'\"$* \t()", str[idx])
		&& ft_strncmp(&str[idx], "&&", 2) && str[idx])
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

static t_node	*lexeme_node(char const **str)
{
	if (!ft_strncmp(*str, "\'", 1))
		return (make_node(get_lexeme(str, 1), LEX_SINGLE_QUOTE));
	if (!ft_strncmp(*str, "\"", 1))
		return (make_node(get_lexeme(str, 1), LEX_DOUBLE_QUOTE));
	if (!ft_strncmp(*str, "<", 1))
		return (make_node(get_lexeme(str, 1), LEX_REDIRECT_IN));
	if (!ft_strncmp(*str, ">", 1))
		return (make_node(get_lexeme(str, 1), LEX_REDIRECT_OUT));
	if (!ft_strncmp(*str, "|", 1))
		return (make_node(get_lexeme(str, 1), LEX_PIPE));
	if (!ft_strncmp(*str, "$", 1))
		return (make_node(get_lexeme(str, 1), LEX_ENV));
	if (!ft_strncmp(*str, "*", 1))
		return (make_node(get_lexeme(str, 1), LEX_WILD));
	if (!ft_strncmp(*str, "(", 1))
		return (make_node(get_lexeme(str, 1), LEX_PARENTHESIS_OPEN));
	if (!ft_strncmp(*str, ")", 1))
		return (make_node(get_lexeme(str, 1), LEX_PARENTHESIS_CLOSE));
}

t_node	*get_node(char const **str)
{
	if (!ft_strncmp(*str, "&&", 2))
		return (make_node(get_lexeme(str, 2), LEX_AND));
	if (!ft_strncmp(*str, ">>", 2))
		return (make_node(get_lexeme(str, 2), LEX_REDIRECT_APP));
	if (!ft_strncmp(*str, "<<", 2))
		return (make_node(get_lexeme(str, 2), LEX_HERE_DOC));
	if (!ft_strncmp(*str, "||", 2))
		return (make_node(get_lexeme(str, 2), LEX_OR));
	if (ft_strchr("\'\"<>|$*()", **str))
		return (lexeme_node(str));
	if (**str == ' ' || **str == '\t')
		return (make_node(get_lexeme(str, whitespace_len(*str)), LEX_WHITE));
	return (make_node(get_lexeme(str, word_len(*str)), LEX_WORD));
}
