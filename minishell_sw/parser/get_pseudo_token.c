/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pseudo_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:40:50 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/03 20:14:17 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	two_len_lexeme(t_node **new_token, char const **str)
{
	if (!ft_strncmp("&&", *str, 2))
		*new_token = make_node(ft_strdup("&&"), LEX_AND);
	else if (!ft_strncmp("||", *str, 2))
		*new_token = make_node(ft_strdup("||"), LEX_OR);
	else if (!ft_strncmp("<<", *str, 2))
		*new_token = make_node(ft_strdup("<<"), LEX_HERE_DOC);
	else if (!ft_strncmp(">>", *str, 2))
		*new_token = make_node(ft_strdup(">>"), LEX_REDIRECT_APP);
	else
		return (FAILURE);
	if (*new_token == NULL)
		exit(MALLOC_FAILURE);
	*str += 2;
	return (SUCCESS);
}

static int	one_len_lexeme(t_node **new_token, char const **str)
{
	if (**str == '(')
		*new_token = make_node(ft_strdup("("), LEX_PARENTHESIS_OPEN);
	else if (**str == ')')
		*new_token = make_node(ft_strdup(")"), LEX_PARENTHESIS_CLOSE);
	else if (**str == '|')
		*new_token = make_node(ft_strdup("|"), LEX_PIPE);
	else if (**str == '<')
		*new_token = make_node(ft_strdup("<"), LEX_REDIRECT_IN);
	else if (**str == '>')
		*new_token = make_node(ft_strdup(">"), LEX_REDIRECT_OUT);
	else if (**str == '$')
		*new_token = make_node(ft_strdup("$"), LEX_ENV);
	else if (**str == '*')
		*new_token = make_node(ft_strdup("*"), LEX_WILD);
	else if (**str == '\'')
		*new_token = make_node(ft_strdup("\''"), LEX_SINGLE_QUOTE);
	else if (**str == '\"')
		*new_token = make_node(ft_strdup("\""), LEX_DOUBLE_QUOTE);
	else
		return (FAILURE);
	if (*new_token == NULL)
		exit(MALLOC_FAILURE);
	++(*str);
	return (SUCCESS);
}

static int	white_space_lexeme(t_node **new_token, char const **str)
{
	char const	*tmp;

	tmp = *str;
	while ((**str) == ' ' || (**str) == '\t')
		++(*str);
	if (tmp == *str)
		return (FAILURE);
	*new_token = make_node(ft_strdup(""), LEX_WHITE);
	if (*new_token == NULL)
		exit(MALLOC_FAILURE);
	return (SUCCESS);
}

static int	word_lexeme(t_node **new_token, char const **str)
{
	char const	*tmp;

	tmp = *str;
	while (**str && !ft_strchr("()<>|\'\"*$ \t", **str) && \
		ft_strncmp("&&", *str, 2))
		++(*str);
	*new_token = make_node(ft_substr(tmp, 0, *str - tmp), LEX_WORD);
	if (*new_token == NULL)
		exit(MALLOC_FAILURE);
	return (SUCCESS);
}

t_node	*get_pseudo_token(char const **str)
{
	t_node	*new_token;

	if (two_len_lexeme(&new_token, str) == SUCCESS)
		return (new_token);
	if (one_len_lexeme(&new_token, str) == SUCCESS)
		return (new_token);
	if (white_space_lexeme(&new_token, str) == SUCCESS)
		return (new_token);
	word_lexeme(&new_token, str);
	return (new_token);
}
