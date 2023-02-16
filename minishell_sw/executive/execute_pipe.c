/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:58:07 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/12 13:50:23 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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
	close_all(info);
	while (++idx < info->process_cnt)
	{
		if (waitpid(info->pid_table[idx], &status, 0) < 0)
			perror_msg(NULL, 1);
	}
	here_doc(NULL, TRUE);
	if ((status & 0xFF) != 0)
		exit((status & 0xFF) + 128);
	else
		exit((status >> 8) & 0xFF);
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
	char	**cmd;

	connect_pipe(info, idx);
	close_all(info);
	cmd = compound_to_char_twoptr(command_tree->right_child);
	manage_redirect(command_tree->left_child);
	if (do_builtin(cmd) == SUCCESS)
		exit(EXIT_SUCCESS);
	if (ft_strchr(cmd[0], '/') != NULL)
		access_check(cmd[0], '/');
	else
	{
		find_path(cmd);
		access_check(cmd[0], '\0');
	}
	execve(cmd[0], cmd, env_to_char());
	write(STDERR_FILENO, SHELL, SHELL_LEN);
	perror_msg(cmd[0], 1);
}

void	pipe_process(t_pipe_info *info, t_tree *cur_tree)
{
	pid_t	pid;
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
