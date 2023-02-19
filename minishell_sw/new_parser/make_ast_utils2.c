/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ast_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:06:55 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/19 10:56:59 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	make_pipe_tree(t_list *pipe_stack, t_tree *cur_tree,
	t_node **cur_token)
{
	t_tree	*pipe_tree;

	pipe_tree = make_tree(AST_PIPE);
	pipe_tree->left_child = cur_tree;
	push(pipe_stack, pipe_tree);
	*cur_token = (*cur_token)->next;
}

static void	make_and_or_tree(t_list *pipe_stack, t_list *and_or_stack,
	t_tree *cur_tree, t_node **cur_token)
{
	t_tree	*and_or_tree;
	t_tree	*operator_tree;

	and_or_tree = make_tree(lex_to_symbol((*cur_token)->lex));
	while (!stack_empty(pipe_stack))
	{
		operator_tree = top(pipe_stack)->val;
		pop(pipe_stack);
		operator_tree->right_child = cur_tree;
		cur_tree = operator_tree;
	}
	and_or_tree->left_child = cur_tree;
	push(and_or_stack, and_or_tree);
	*cur_token = (*cur_token)->next;
}

static t_tree	*make_total_tree(t_list *pipe_stack, t_list *and_or_stack,
	t_tree *cur_tree, t_node **cur_token)
{
	t_tree	*operator_tree;

	while (!stack_empty(pipe_stack))
	{
		operator_tree = top(pipe_stack)->val;
		pop(pipe_stack);
		operator_tree->right_child = cur_tree;
		cur_tree = operator_tree;
	}
	while (!stack_empty(and_or_stack))
	{
		operator_tree = top(and_or_stack)->val;
		pop(and_or_stack);
		operator_tree->right_child = cur_tree;
		cur_tree = operator_tree;
	}
	*cur_token = (*cur_token)->next;
	return (cur_tree);
}

static t_tree	*free_stack_and_return(t_list *pipe_stack, t_list *and_or_stack,
	t_tree *ret)
{
	free_list(pipe_stack, 0, LEX);
	free_list(and_or_stack, 0, LEX);
	return (ret);
}

t_tree	*make_expression(t_node **cur_token)
{
	t_tree	*cur_tree;
	t_list	*pipe_stack;
	t_list	*and_or_stack;

	pipe_stack = make_list(LEX);
	and_or_stack = make_list(LEX);
	while ((*cur_token)->lex != -1)
	{
		if (is_compound_redirect((*cur_token)->lex) \
			|| (*cur_token)->lex == LEX_PARENTHESIS_OPEN)
			cur_tree = make_empty_tree(cur_token);
		else if ((*cur_token)->lex == LEX_PIPE)
			make_pipe_tree(pipe_stack, cur_tree, cur_token);
		else if ((*cur_token)->lex == LEX_AND || (*cur_token)->lex == LEX_OR)
			make_and_or_tree(pipe_stack, and_or_stack, cur_tree, cur_token);
		else if ((*cur_token)->lex == LEX_PARENTHESIS_CLOSE)
		{
			cur_tree = make_total_tree(pipe_stack, and_or_stack,
					cur_tree, cur_token);
			return (free_stack_and_return(pipe_stack, and_or_stack, cur_tree));
		}
	}
	return (free_stack_and_return(pipe_stack, and_or_stack, cur_tree));
}
