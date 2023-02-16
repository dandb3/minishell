/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:11:30 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/15 20:24:18 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	get_status(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		perror_msg(NULL, 1);
	if ((status & 0xff) == 0)
		return ((status >> 8) & 0xff);
	if ((status & 0xff) != 0xff && (status & 0xff) != 0)
		return (128 + (status & 0xff));
	return (status >> 8);
}

static int	execute_pipe(t_tree *cur)
{
	t_pipe_info	info;

	init_pipeinfo(&info, cur);
	pipe_process(&info, cur);
	free(info.fds);
	free(info.pid_table);
	return (SUCCESS);
}

static int	execute_parentheses(t_tree *cur)
{
	t_redir_fds	red_info;
	pid_t		pid;
	int			status;

	ft_memset(&red_info, 0, sizeof(t_redir_fds));
	pid = fork();
	if (pid < 0)
		perror_msg(NULL, 1);
	if (pid != 0)
		return (get_status(pid));
	return (execute(cur->left));
}

static int	execute_compound(t_tree *cur)
{
	char	**cmds;
	pid_t	pid;

	cmds = compound_to_char_twoptr(cur->right_child->val);
	if (do_builtin(cmds) == SUCCESS)
	{
		close_redirect(&red_info, -1, -1);
		free_twoptr(cmds, 0)
		return (get_exitcode());
	}
	pid = fork();
	if (pid < 0)
		perror_msg(NULL, 1);
	if (pid != 0)
	{
		free_twoptr(cmds);
		return (get_status(pid));
	}
	else
		if (execve(cmds[idx][0], cmds[idx], env_to_char()) == -1)
			perror_msg(cmds[idx][0], 126);
}

static int	execute_command(t_tree *cur)
{
	t_redir_fds	red_info;

	ft_memset(&red_info, 0, sizeof(t_redir_fds));
	manage_redirect(cur->left_child, &red_info);
	if (cur->right_child->symbol == AST_PARENTHESESES)
		execute_parentheses(cur->right_child);
	else
		execute_compound(cur->right_child);
	close_redirect(&red_info, -1, -1);
	return (SUCCESS);
}

int	execute(t_tree *cur, int prev_status)
{
	int	status;

	if (!cur)
		return (prev_status);
	if (cur->symbol == AST_PIPE)
		status = execute_pipe(cur);
	else if (cur->symbol == AST_AND || cur->symbol == AST_OR)
	{
		status = execute(cur->left_child, 0);
		if (cur->symbol == AST_AND && !status)
			status = execute(cur->right_child, status);
		if (cur->symbol == AST_OR && status)
			status = execute(cur->right_child, status);
	}
	else if (cur->symbol == AST_PARENTHESESES)
		status = execute_parentheses(cur);
	else if (cur->symbol == AST_COMMAND)
		status = execute_command(cur);
	return (status);
}
