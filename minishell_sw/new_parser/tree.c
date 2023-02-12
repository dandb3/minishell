/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:16:44 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/11 19:23:06 by jdoh             ###   ########seoul.kr  */
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
	return (new_tree);
}

void	*free_tree(t_tree *root)
{
	if (root == NULL)
		return (NULL);
	free_tree(root->left_child);
	free_tree(root->right_child);
	if (root->symbol == AST_HERE_DOC)
		free(root->val);
	free(root);
	return (NULL);
}
