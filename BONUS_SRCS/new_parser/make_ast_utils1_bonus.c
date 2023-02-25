/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ast_utils1_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:06:13 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/25 13:03:43 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"

static void	make_subshell(t_tree *subroot, t_node **cur_token)
{
	*cur_token = (*cur_token)->next;
	subroot->right_child = make_tree(AST_PARENTHESESES);
	subroot->right_child->left_child
		= make_expression(cur_token);
}

static void	add_redirect(t_tree *subroot, t_node **cur_token)
{
	t_tree	*new_tree;
	t_lex	lex;

	new_tree = make_tree(lex_to_symbol((*cur_token)->lex));
	lex = (*cur_token)->lex;
	*cur_token = (*cur_token)->next;
	if (lex == LEX_HERE_DOC)
		new_tree->val = copy_val(*cur_token);
	else
		new_tree->val = copy_list((*cur_token)->val);
	new_tree->left_child = subroot->left_child;
	subroot->left_child = new_tree;
	*cur_token = (*cur_token)->next;
}

static void	add_compound(t_tree *subroot, t_node **cur_token)
{
	t_tree	*new_tree;

	new_tree = make_tree(AST_COMPOUND);
	new_tree->val = copy_list((*cur_token)->val);
	new_tree->right_child = subroot->right_child;
	subroot->right_child = new_tree;
	*cur_token = (*cur_token)->next;
}

t_tree	*make_empty_tree(t_node **cur_token)
{
	t_tree	*subroot;

	subroot = make_tree(AST_COMMAND);
	if ((*cur_token)->lex == LEX_PARENTHESIS_OPEN)
		make_subshell(subroot, cur_token);
	while (is_compound_redirect((*cur_token)->lex))
	{
		if (is_redirect((*cur_token)->lex))
			add_redirect(subroot, cur_token);
		else
			add_compound(subroot, cur_token);
	}
	return (subroot);
}
