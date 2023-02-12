/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:11:30 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/12 18:23:48 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	execute_pipe(t_tree *cur)
{
	t_pipe_info	info;

	info = init_pipeinfo(cur);
	return (pipe_process(info));
}

static int	execute_parentheses(t_tree *cur)
{
	t_tree	*to_exec;
	pid_t	pid;
	int		status;

	to_exec = cur->left;
	if (cur->right)
	{
		manage_redirect(to_exec);
		to_exec = cur->right;
	}
	pid = fork();
	if (pid < 0)
		perror_msg(NULL, 1);
	if (pid != 0)
	{
		if (waitpid(pid, &status, 0) == -1)
			perror_msg(NULL, 1);
		if ((status & 0xff) == 0)
			return ((status >> 8) & 0xff);
		else if ((status & 0xff) != 0xff && (status & 0xff) != 0)
			return (128 + (status & 0xff));
	}
	else
		return (execute(to_exec));
}

// where is redirect?
static int	execute_compound(t_tree *cur)
{
	char	**cmds;
	pid_t	pid;
	int		status;

	if (cur->left)
		manage_redirect(cur->left);
	cmds = compound_to_char_twoptr(cur->val);
	if (do_builtin(cmds) == SUCCESS)
		return (get_exitcode());
	pid = fork();
	if (pid < 0)
		perror_msg(NULL, 1);
	if (pid != 0)
		if (waitpid(pid, &status, 0) == -1)
			perror_msg(NULL, 1);
	else
		if (execve(cmds[idx][0], cmds[idx], env_to_char()) == -1)
			perror_msg(cmds[idx][0], 126);
	return (status);
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
	else if (cur->symbol == AST_COMPOUND)
		status = execute_compound(cur);
	return (status);
}
