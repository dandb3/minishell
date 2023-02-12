/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:37:31 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/12 10:44:42 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	count_process(t_tree *cur)
{
	int	process_cnt;

	process_cnt = 2;
	while (cur->right_child && cur->right_child->symbol == AST_PIPE)
	{
		++process_cnt;
		cur = cur->right_child;
	}
	return (process_cnt);
}

static char	***put_cmds(t_tree *cur, int process_cnt)
{
	int		idx;
	char	***cmds;

	cmds = (char ***)ft_calloc(process_cnt + 1, sizeof(char **));
	if (!cmds)
		exit(MALLOC_FAILURE);
	idx = -1;
	while (cur && cur->symbol == AST_PIPE)
	{
		cmds[++idx] = compound_to_char_twoptr((t_list *)cur->left_child->val);
		cur = cur->right_child;
	}
	cmds[++idx] = compound_to_char_twoptr((t_list *)cur->right_child->val);
	cur = cur->right_child;
	return (cmds);
}

t_pipe_info	*init_pipeinfo(t_tree *cur)
{
	t_pipe_info	*info;

	info = (t_pipe_info *)ft_calloc(1, sizeof(t_pipe_info));
	if (!info)
		exit(MALLOC_FAILURE);
	info->process_cnt = count_process(cur);
	info->cmds = put_cmds(cur, process_cnt);
	return (info);
}
