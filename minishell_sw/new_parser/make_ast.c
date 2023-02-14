/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:12:46 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/14 13:08:16 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_tree	*make_subshell(t_tree *subroot, t_node **cur_token)
{
	*cur_token = (*cur_token)->next;
	subroot->right_child = make_tree(AST_PARENTHESESES);
	subroot->right_child->left_child
		= make_expression(cur_token);
	return (subroot);
}

void	add_redirect(t_tree *subroot, t_node **cur_token)
{
	t_tree	*new_tree;

	new_tree = make_tree(lex_to_symbol((*cur_token)->lex));
	*cur_token = (*cur_token)->next;
	new_tree->val = copy_val(*cur_token);
	new_tree->left_child = subroot->left_child;
	subroot->left_child = new_tree;
	*cur_token = (*cur_token)->next;
}

void	add_compound(t_tree *subroot, t_node **cur_token)
{
	t_tree	*new_tree;

	new_tree = make_tree(AST_COMPOUND);
	new_tree->val = copy_val(*cur_token);
	new_tree->right_child = subroot->right_child;
	subroot->right_child = new_tree;
	*cur_token = (*cur_token)->next;
}

t_tree	*make_empty_tree(t_node **cur_token)
{
	t_tree	*subroot;

	subroot = make_tree(AST_COMMAND);
	if ((*cur_token)->lex == LEX_PARENTHESIS_OPEN)
		return (make_subshell(subroot, cur_token));
	while (is_compound_redirect((*cur_token)->lex))
	{
		if (is_redirect((*cur_token)->lex))
			add_redirect(subroot, cur_token);
		else
			add_compound(subroot, cur_token);
	}
	return (subroot);
}

void	make_pipe_tree(t_list *pipe_stack, t_tree *cur_tree,
	t_node **cur_token)
{
	t_tree	*pipe_tree;

	pipe_tree = make_tree(AST_PIPE);
	pipe_tree->left_child = cur_tree;
	push(pipe_stack, pipe_tree);
	*cur_token = (*cur_token)->next;
}

void	make_and_or_tree(t_list *pipe_stack, t_list *and_or_stack,
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

t_tree	*make_total_tree(t_list *pipe_stack, t_list *and_or_stack,
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
			cur_tree = make_total_tree(pipe_stack, and_or_stack, cur_tree, cur_token);
	}
	free_list(pipe_stack, 0, LEX);
	free_list(and_or_stack, 0, LEX);
	return (cur_tree);
}

t_tree	*make_ast(t_list *token_list)
{
	t_tree	*root;
	t_node	*cur_token;
	char	*val;

	val = ft_strdup("");
	if (val == NULL)
		exit(MALLOC_FAILURE);
	push_node(make_node(val, LEX_PARENTHESIS_CLOSE), token_list);
	cur_token = token_list->head->next;
	return (make_expression(&cur_token));
}
