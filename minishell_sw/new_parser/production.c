/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   production.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:30:20 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/12 16:39:15 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	pop_push_exception(t_list *stack, t_tree *cur_tree)
{
	t_tree	*nulltree;

	pop(stack);
	cur_tree->right_child = make_tree(AST_E4);
	push(stack, cur_tree->right_child);
	cur_tree->left_child = make_tree(-1);
	nulltree = cur_tree->left_child;
	nulltree->right_child = make_tree(AST_PARENTHESESES);
	nulltree->left_child = make_tree(AST_E0);
	push(stack, make_tree(AST_PARENTHESES_CLOSE));
	push(stack, nulltree->left_child);
	push(stack, make_tree(AST_PARENTHESES_OPEN));
}

static void	pop_push2(t_list *stack, t_tree *cur_tree, t_symbol s1, t_symbol s2)
{
	pop(stack);
	if (s2 >= 0)
	{
		cur_tree->right_child = make_tree(s2);
		push(stack, cur_tree->right_child);
	}
	if (s1 >= 0)
	{
		cur_tree->left_child = make_tree(s1);
		push(stack, cur_tree->left_child);
	}
}

static void	production_exception(t_list *stack, t_tree *cur_tree,
	t_table table_result)
{
	if (table_result == E8_REDIRECT_IN)
		pop_push2(stack, cur_tree, AST_REDIRECT_IN, AST_COMPOUND);
	if (table_result == E8_REDIRECT_OUT)
		pop_push2(stack, cur_tree, AST_REDIRECT_OUT, AST_COMPOUND);
	if (table_result == E8_REDIRECT_APPEND)
		pop_push2(stack, cur_tree, AST_REDIRECT_APPEND, AST_COMPOUND);
	if (table_result == E8_HERE_DOC)
		pop_push2(stack, cur_tree, AST_HERE_DOC, AST_COMPOUND);
	if (table_result == E5_PARENTHESES)
		pop_push_exception(stack, cur_tree);
}

void	production(t_list *stack, t_tree *cur_tree, t_table table_result)
{
	if (table_result == E0_E2_E1)
		pop_push2(stack, cur_tree, AST_E2, AST_E1);
	if (table_result == E1_OR_E0)
		pop_push2(stack, cur_tree, AST_OR, AST_E0);
	if (table_result == E1_AND_E0)
		pop_push2(stack, cur_tree, AST_AND, AST_E0);
	if (table_result == E1_EPSILON || table_result == E3_EPSILON \
		|| table_result == E4_EPSILON || table_result == E6_EPSILON)
		pop_push2(stack, cur_tree, AST_EPSILON, -1);
	if (table_result == E2_E5_E3)
		pop_push2(stack, cur_tree, AST_E5, AST_E3);
	if (table_result == E3_PIPE_E2)
		pop_push2(stack, cur_tree, AST_PIPE, AST_E2);
	if (table_result == E4_E8_E4)
		pop_push2(stack, cur_tree, AST_E8, AST_E4);
	if (table_result == E5_E7_E6 || table_result == E6_E7_E6)
		pop_push2(stack, cur_tree, AST_E7, AST_E6);
	if (table_result == E7_COMP_E8)
		pop_push2(stack, cur_tree, AST_COMPOUND, AST_E8);
	else
		production_exception(stack, cur_tree, table_result);
}
