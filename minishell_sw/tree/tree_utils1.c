/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:38:16 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/09 19:47:39 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

t_element	*make_tree(void)
{
	t_element	*root;

	root = (t_element *)ft_calloc(1, sizeof(t_element));
	if (!root)
		exit(MALLOC_FAILURE);
	return (root);
}

t_element	*make_element(void *val, t_parse ptype)
{
	t_element	*elem;

	elem = (t_element *)ft_calloc(1, sizeof(t_element));
	if (!elem)
		exit(MALLOC_FAILURE);
	elem->val = val;
	elem->ptype = ptype;
	return (elem);
}

int	is_leaf(t_element *elem)
{
	if (!(elem->left) && !(elem->right))
		return (TRUE);
	return (FALSE);
}

void	visit_element(t_element *cur)
{
	(void) cur;
}

void	traverse_tree(t_element	*cur)
{
	if (is_leaf(cur))
		return ;
	traverse_tree(cur->left);
	visit_element(cur);
	traverse_tree(cur->right);
}
