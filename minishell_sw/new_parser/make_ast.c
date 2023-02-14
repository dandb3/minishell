/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:12:46 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/13 21:23:04 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_tree	*make_empty_tree(__attribute__((unused)) t_list *pipe_stack,
	__attribute__((unused)) t_list *and_or_stack,
		__attribute__((unused)) t_tree *cur_tree, t_node **cur_token)
{
	t_tree	*subroot;
	t_tree	*new_node;

	subroot = make_tree(AST_COMMAND);
	while (is_compound_redirect((*cur_token)->lex) \
		|| (*cur_token)->lex == LEX_PARENTHESIS_OPEN)
	{
		new_node = make_tree(lex_to_symbol((*cur_token)->lex));
		if ((*cur_token)->lex == LEX_PARENTHESIS_OPEN)
		{
			*cur_token = (*cur_token)->next;
			new_node->symbol = AST_PARENTHESESES;
			subroot->right_child = new_node;
			new_node->left_child = make_subshell(cur_token, pipe_stack,
					and_or_stack);
			return (subroot);
		}
		if (is_redirect((*cur_token)->lex))
		{
			*cur_token = (*cur_token)->next;
			new_node->val = copy_val((*cur_token)->val);
			new_node->left_child = subroot->left_child;
			subroot->left_child = new_node;
		}
		else
		{
			new_node->val = copy_val((*cur_token)->val);
			new_node->right_child = subroot->right_child;
			subroot->right_child = new_node;
		}
		*cur_token = (*cur_token)->next;
	}
	return (subroot);
}

t_tree	*make_subshell(t_node **cur_token, t_list *pipe_stack,
	t_list *and_or_stack)
{
	t_tree	*cur_tree;

	while ((*cur_token)->val != LEX_PARENTHESIS_CLOSE)
	{
		if (is_compound_redirect((*cur_token)->lex) \
			|| (*cur_token)->lex == LEX_PARENTHESIS_OPEN)
			cur_tree = make_empty_tree(pipe_stack, and_or_stack, cur_tree,
					cur_token);
		else if ((*cur_token)->lex == LEX_PIPE)
			make_pipe_tree(pipe_stack, and_or_stack, cur_tree, cur_token);
		else if ((*cur_token)->lex == LEX_AND || (*cur_token)->lex == LEX_OR)
			make_and_or_tree(pipe_stack, and_or_stack, cur_tree, cur_token);
		else if ((*cur_token)->lex == LEX_PARENTHESIS_CLOSE)
			make_total_tree(pipe_stack, and_or_stack, cur_tree, cur_token);
	}
}

t_tree	*make_ast(t_list *token_list)
{
	t_tree	*root;
	t_node	*cur_token;
	t_list	*pipe_stack;
	t_list	*and_or_stack;
	char	*val;

	pipe_stack = make_list(LEX);
	and_or_stack = make_list(LEX);
	val = ft_strdup("");
	if (val == NULL)
		exit(MALLOC_FAILURE);
	push_node(make_node(val, LEX_PARENTHESIS_CLOSE), token_list);
	cur_token = token_list->head->next;
	root = make_subshell(&cur_token);
	while (!stack_empty(pipe_stack))
		pop(pipe_stack);
	while (!stack_empty(and_or_stack))
		pop(and_or_stack);
	free_list(pipe_stack, 0, LEX);
	free_list(and_or_stack, 0, LEX);
	return (make_subshell(&cur_token));
}
