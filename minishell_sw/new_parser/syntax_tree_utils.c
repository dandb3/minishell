/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 22:19:54 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/11 23:02:51 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*init(char **table, t_list **stack, t_tree **root,
	t_list *token_list)
{
	*stack = make_list(NAME);
	*root = make_tree(AST_E0);
	push(*stack, *root);
	make_parsing_table(table);
	return (token_list->head->next);
}

t_symbol	lex_to_symbol(t_lex lex)
{
	if (lex == -1)
		return (-1);
	return (lex + 3);
}

int	is_terminal(t_symbol symbol)
{
	if (symbol >= AST_COMPOUND && symbol <= AST_REDIRECT_APPEND)
		return (1);
	return (0);
}

int	table_idx(t_lex lex)
{
	if (lex == -1)
		return (10);
	return (lex - 6);
}

void	insert_and_pop(t_list *stack, t_tree *cur_tree, t_node *cur_token)
{
	cur_tree->val = cur_token->val;
	pop(stack);
}
