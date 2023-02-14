/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:28:00 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/13 20:51:07 by jdoh             ###   ########.fr       */
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
