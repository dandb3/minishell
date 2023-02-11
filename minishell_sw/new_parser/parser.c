/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:07:55 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/11 18:15:40 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	make_parsing_table(char **table)
{
	table[AST_E0] = "\1\0\0\0\1\0\1\1\1\1\0";
	table[AST_E1] = "\0\2\3\0\0\4\0\0\0\0\4";
	table[AST_E2] = "\5\0\0\0\5\0\5\5\5\5\0";
	table[AST_E3] = "\0\7\7\6\0\7\0\0\0\0\7";
	table[AST_E4] = "\0\11\11\11\0\11\10\10\10\10\11";
	table[AST_E5] = "\13\0\0\0\12\0\13\13\13\13\0";
	table[AST_E6] = "\14\15\15\15\0\15\14\14\14\14\15";
	table[AST_E7] = "\16\0\0\0\0\0\17\17\17\17\0";
	table[AST_E8] = "\0\0\0\0\0\0\20\21\22\23\0";
}

t_tree	*parser(t_list *env_list, char const *input)
{
	t_list	*token_list;
	t_tree	*syntax_tree;
	char	*table[9];

	if (make_token_list(&token_list, env_list, input) == FAILURE)
		return (NULL);
	make_parsing_table(table);
	syntax_tree = make_syntax_tree(token_list, table);
	if (syntax_tree == NULL)
}
