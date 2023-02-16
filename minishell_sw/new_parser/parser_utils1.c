/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 22:19:54 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/14 16:54:07 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	syntax_init(t_node **cur_token, t_list **stack, t_list *token_list)
{
	*cur_token = token_list->head->next;
	*stack = make_list(LEX);
	push(*stack, make_tree(AST_E0));
}

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
