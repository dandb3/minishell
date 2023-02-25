/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:11:30 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/25 13:03:43 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_bonus.h"

static int	execute_pipe(t_tree *cur)
{
	t_pipe_info	info;
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid < 0)
		perror_msg(NULL, 1);
	if (pid != 0)
	{
		status = get_status(pid);
		return (status);
	}
	init_pipeinfo(&info, cur);
	pipe_process(&info, cur);
	return (FAILURE);
}

static int	execute_parentheses(t_tree *cur)
{
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid < 0)
		perror_msg(NULL, 1);
	if (pid != 0)
	{
		status = get_status(pid);
		return (status);
	}
	exit(execute(cur->left_child, 0));
	return (FAILURE);
}

static int	execute_compound(t_tree *cur)
{
	char	**cmd;
	char	**path_split;
	pid_t	pid;
	int		status;

	cmd = compound_to_char_twoptr(cur);
	if (do_builtin(cmd) == SUCCESS)
		return (get_exitcode() + free_twoptr(cmd, 0));
	if (cmd[0] == NULL)
		return (free_twoptr(cmd, 0));
	pid = fork();
	if (pid < 0)
		perror_msg(NULL, 1);
	if (pid != 0)
	{
		status = get_status(pid);
		return (free_twoptr(cmd, status));
	}
	path_split = make_path_split();
	add_path_and_access_check(path_split, cmd);
	set_signal(SG_CHILD);
	execve(cmd[0], cmd, env_to_char());
	perror_msg(cmd[0], 127);
	return (FAILURE);
}

int	execute_command(t_tree *cur)
{
	int	status;

	status = manage_redirect(cur->left_child);
	if (status != SUCCESS)
		return (status);
	if (cur->right_child == NULL)
		return (status);
	if (cur->right_child->symbol == AST_PARENTHESESES)
		status = execute_parentheses(cur->right_child);
	else
		status = execute_compound(cur->right_child);
	return (status);
}

int	execute(t_tree *cur, int prev_status)
{
	int	status;

	status = prev_status;
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
