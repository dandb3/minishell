/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 22:19:54 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/19 21:09:14 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_symbol	lex_to_symbol(t_lex lex)
{
	if (lex == -1)
		return (-1);
	return (lex + 3);
}

int	table_idx(t_lex lex)
{
	if (lex == -1)
		return (10);
	return (lex - 6);
}
