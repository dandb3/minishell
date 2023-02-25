/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:58:07 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/25 13:03:43 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_bonus.h"

static void	close_all(t_pipe_info *info)
{
	int	idx;

	idx = -1;
	while (++idx < info->process_cnt - 1)
	{
		if (close(info->fds[idx][0]) < 0)
			perror_msg(NULL, 1);
		if (close(info->fds[idx][1]) < 0)
			perror_msg(NULL, 1);
	}
}

static void	parent_process(t_pipe_info *info)
{
	int	status;
	int	idx;

	idx = -1;
	set_signal(SG_STOP);
	close_all(info);
	while (++idx < info->process_cnt)
	{
		if (waitpid(info->pid_table[idx], &status, 0) < 0)
			perror_msg(NULL, 1);
	}
	here_doc(NULL, TRUE);
	if ((status & 0xff) == 0)
		exit((status >> 8) & 0xff);
	if ((status & 0xff) != 0xff && (status & 0xff) != 0)
		exit(128 + (status & 0xff));
	exit(status >> 8);
}

static void	connect_pipe(t_pipe_info *info, int idx)
{
	if (idx != 0 && dup2(info->fds[idx - 1][0], STDIN_FILENO) == FAILURE)
		perror_msg(NULL, 1);
	if (idx != info->process_cnt - 1 \
		&& dup2(info->fds[idx][1], STDOUT_FILENO) == FAILURE)
		perror_msg(NULL, 1);
}

static void	child_process(t_pipe_info *info, int idx, t_tree *command_tree)
{
	connect_pipe(info, idx);
	close_all(info);
	exit(execute_command(command_tree));
}

void	pipe_process(t_pipe_info *info, t_tree *cur_tree)
{
	int		idx;

	idx = -1;
	while (++idx < info->process_cnt)
	{
		info->pid_table[idx] = fork();
		if (info->pid_table[idx] < 0)
			perror_msg(NULL, 1);
		if (info->pid_table[idx] == 0)
		{
			if (cur_tree->symbol == AST_PIPE)
				child_process(info, idx, cur_tree->left_child);
			else
				child_process(info, idx, cur_tree);
		}
		cur_tree = cur_tree->right_child;
	}
	parent_process(info);
}
