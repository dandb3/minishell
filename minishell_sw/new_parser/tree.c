/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:16:44 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/14 16:57:45 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_tree	*make_tree(t_symbol symbol)
{
	t_tree	*new_tree;

	new_tree = (t_tree *) malloc(sizeof(t_tree));
	if (new_tree == NULL)
		exit(MALLOC_FAILURE);
	new_tree->left_child = NULL;
	new_tree->right_child = NULL;
	new_tree->symbol = symbol;
	new_tree->val = NULL;
	return (new_tree);
}

void	free_tree(t_tree *root)
{
	if (root == NULL)
		return (NULL);
	free_tree(root->left_child);
	free_tree(root->right_child);
	if (root->symbol == AST_HERE_DOC)
		free(root->val);
	else if (root->symbol == AST_COMPOUND || root->symbol == AST_REDIRECT_APPEND
		|| root->symbol == AST_REDIRECT_IN || root->symbol == AST_REDIRECT_OUT)
		free_list(root->val, 0, LEX);
	free(root);
}
