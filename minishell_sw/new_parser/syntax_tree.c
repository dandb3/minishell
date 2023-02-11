/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:16:21 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/11 19:27:00 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_node	*init(char **table, t_list **stack, t_tree **root,
	t_list *token_list)
{
	*stack = make_list(NAME);
	*root = make_tree(AST_E0);
	push(*stack, *root);
	make_parsing_table(table);
	return (token_list->head->next);
}

static t_symbol	lex_to_symbol(t_lex lex)
{
	if (lex == -1)
		return (-1);
	return (lex + 3);
}

static int	is_terminal(t_symbol symbol)
{
	if (symbol >= AST_COMPOUND && symbol <= AST_REDIRECT_APPEND)
		return (1);
	return (0);
}

static int	table_idx(t_lex lex)
{
	if (lex == -1)
		return (10);
	return (lex - 6);
}

t_tree	*make_syntax_tree(t_list *token_list, char **table)
{
	t_list	*stack;
	t_tree	*root;
	t_node	*cur_token;
	t_tree	*cur_tree;
	int		token_idx;

	cur_token = init(table, &stack, &root, token_list);
	while (!stack_empty(stack))
	{
		cur_tree = top(stack)->val;
		token_idx = table_idx(cur_token->lex);
		if (cur_tree->symbol == AST_EPSILON)
			pop(stack);
		else if (cur_tree->symbol == lex_to_symbol(cur_token->lex))
		{
			pop(stack);
			cur_token = cur_token->next;
		}
		else if (is_terminal(cur_tree->symbol)
			|| table[cur_tree->symbol][token_idx] == SYNTAX_ERROR)
			return (error_manage(cur_token, root, stack));
		else
			production(stack, cur_tree, table[cur_tree->symbol][token_idx]);
	}
	return (root);
}