/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:16:21 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/17 19:44:39 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	syntax_check(t_list *token_list, char **table)
{
	t_list	*stack;
	t_tree	*cur_tree;
	t_node	*cur_token;
	int		token_idx;

	syntax_init(&cur_token, &stack, token_list);
	while (!stack_empty(stack))
	{
		cur_tree = top(stack)->val;
		token_idx = table_idx(cur_token->lex);
		if (cur_tree->symbol == AST_EPSILON)
			pop_tree(stack);
		else if (cur_tree->symbol == lex_to_symbol(cur_token->lex))
			here_doc_or_pop(stack, &cur_token, cur_tree->symbol);
		else if (is_terminal(cur_tree->symbol)
			|| table[cur_tree->symbol][token_idx] == SYNTAX_ERROR)
			return (error_manage(cur_token, stack));
		else
			production(stack, table[cur_tree->symbol][token_idx]);
	}
	if (cur_token->next != NULL)
		return (error_manage(cur_token, stack));
	free_list(stack, 0, LEX);
	return (SUCCESS);
}
