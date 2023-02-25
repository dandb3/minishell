/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:37:31 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/25 13:03:43 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_bonus.h"

char	**make_path_split(void)
{
	char	**result;
	char	*path;

	path = find_env_val("PATH");
	if (path == NULL)
		return (NULL);
	result = ft_split(path, ':');
	free(path);
	if (result == NULL)
		exit(MALLOC_FAILURE);
	return (result);
}

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

void	init_pipeinfo(t_pipe_info *info, t_tree *cur)
{
	int	idx;

	info->path_split = make_path_split();
	info->process_cnt = count_process(cur);
	info->fds = (int (*)[2]) malloc(sizeof(int [2]) * (info->process_cnt - 1));
	info->pid_table = (pid_t *) malloc(sizeof(pid_t) * info->process_cnt);
	if (info->fds == NULL || info->pid_table == NULL)
		exit(MALLOC_FAILURE);
	idx = -1;
	while (++idx < info->process_cnt - 1)
	{
		if (pipe(info->fds[idx]) == FAILURE)
			perror_msg(NULL, 1);
	}
}
