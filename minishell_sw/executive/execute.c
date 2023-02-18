/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:11:30 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/18 20:10:01 by sunwsong         ###   ########.fr       */
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
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid < 0)
		perror_msg(NULL, 1);
	if (pid != 0)
	{
		set_signal(SG_STOP);
		status = get_status(pid);
		set_signal(SG_RUN);
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
		set_signal(SG_STOP);
		status = get_status(pid);
		set_signal(SG_RUN);
		return (status);
	}
	exit(execute(cur->left_child, 0));
	return (FAILURE);
}

void	print_chartwoptr(char **cmds) // 지우세용
{
	printf("print char two ptr go\n");
	while (*cmds)
	{
		printf("%s\n", *cmds);
		++cmds;
	}
}

static int	execute_compound(t_tree *cur)
{
	char	**cmds;
	char	**path_split;
	pid_t	pid;
	int		status;

	cmds = compound_to_char_twoptr(cur);
	if (do_builtin(cmds) == SUCCESS)
		return (get_exitcode() + free_twoptr(cmds, 0));
	pid = fork();
	if (pid < 0)
		perror_msg(NULL, 1);
	if (pid != 0)
	{
		set_signal(SG_STOP);
		free_twoptr(cmds, 0);
		status = get_status(pid);
		set_signal(SG_RUN);
		return (status);
	}
	path_split = make_path_split();
	add_path_and_access_check(path_split, cmds);
	set_signal(SG_CHILD);
	execve(cmds[0], cmds, env_to_char());
	perror_msg(cmds[0], 1);
	return (FAILURE);
}

static int	execute_command(t_tree *cur)
{
	manage_redirect(cur->left_child);
	if (cur->right_child == NULL)
		return (SUCCESS);
	if (cur->right_child->symbol == AST_PARENTHESESES)
		return (execute_parentheses(cur->right_child));
	return (execute_compound(cur->right_child));
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
