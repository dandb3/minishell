/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:39:43 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/18 19:33:57 by sunwsong         ###   ########.fr       */
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
	char	*str;
	int		depth;

	depth = get_compound_tree_depth(cur);
	cmd = (char **)ft_calloc(depth + 1, sizeof(char *));
	if (!cmd)
		exit(MALLOC_FAILURE);
	while (depth--)
	{
		str = expand_char(cur->val);
		if (str == NULL)
		{
			cmd[depth] = ft_strdup("");
			if (!cmd[depth])
				exit(MALLOC_FAILURE);
		}
		else
			cmd[depth] = str;
		cur = cur->right_child;
	}
	return (cmd);
}
