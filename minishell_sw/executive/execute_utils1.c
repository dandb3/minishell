/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:39:43 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/15 15:49:10 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	get_compound_tree_depth(t_tree *cur)
{
	int	idx;

	idx = 0;
	while (cur)
	{
		cur = cur->right_child;
		++idx;
	}
	return (idx);
}

char	**compound_to_char_twoptr(t_tree *cur)
{
	char	**cmd;
	int		depth;

	depth = get_compound_tree_depth(cur);
	cmd = (char **)ft_calloc(depth + 1, sizeof(char *));
	if (!cmd)
		exit(MALLOC_FAILURE);
	while (depth--)
	{
		cmd[depth] = expand_char(cur->val);
		if (!cmd[depth])
			exit(MALLOC_FAILURE);
		cur = cur->right_child;
	}
	return (cmd);
}
