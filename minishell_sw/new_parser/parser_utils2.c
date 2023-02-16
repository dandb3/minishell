/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:28:00 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/14 16:54:24 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_redirect(t_lex lex)
{
	if (lex == LEX_HERE_DOC || lex == LEX_REDIRECT_APP \
		|| lex == LEX_REDIRECT_IN || lex == LEX_REDIRECT_OUT)
		return (1);
	return (0);
}

int	is_compound_redirect(t_lex lex)
{
	if (lex == LEX_COMPOUND || is_redirect(lex))
		return (1);
	return (0);
}

int	is_terminal(t_symbol symbol)
{
	if (symbol >= AST_COMPOUND && symbol <= AST_REDIRECT_APPEND)
		return (1);
	return (0);
}
