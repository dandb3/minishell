/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:11:30 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/18 20:59:01 by sunwsong         ###   ########.fr       */
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
	char	**cmd;
	char	**path_split;
	pid_t	pid;
	int		status;

	cmd = compound_to_char_twoptr(cur);
	if (do_builtin(cmd) == SUCCESS)
		return (get_exitcode() + free_twoptr(cmd, 0));
	pid = fork();
	if (pid < 0)
		perror_msg(NULL, 1);
	if (pid != 0)
	{
		set_signal(SG_STOP);
		free_twoptr(cmd, 0);
		status = get_status(pid);
		set_signal(SG_RUN);
		return (status);
	}
	path_split = make_path_split();
	add_path_and_access_check(path_split, cmd);
	set_signal(SG_CHILD);
	execve(cmd[0], cmd, env_to_char());
	perror_msg(cmd[0], 1);
	return (FAILURE);
}

static int	redirection_return(int red_in, int red_out, int ret)
{
	if (dup2(red_in, STDIN_FILENO) == FAILURE)
		perror_msg(NULL, 1);
	if (dup2(red_out, STDOUT_FILENO) == FAILURE)
		perror_msg(NULL, 1);
	if (close(red_in) == FAILURE)
		perror_msg(NULL, 1);
	if (close(red_out) == FAILURE)
		perror_msg(NULL, 1);
	return (ret);
}

static void	redirection_set(int *red_in, int *red_out)
{
	*red_in = dup(STDIN_FILENO);
	*red_out = dup(STDOUT_FILENO);
	if (*red_in == FAILURE || *red_out == FAILURE)
		perror_msg(NULL, 1);
}

static int	execute_command(t_tree *cur)
{
	int	red_in;
	int	red_out;
	int	status;

	redirection_set(&red_in, &red_out);
	status = manage_redirect(cur->left_child);
	if (status != SUCCESS)
		return (redirection_return(red_in, red_out, status));
	if (cur->right_child == NULL)
		return (redirection_return(red_in, red_out, SUCCESS));
	if (cur->right_child->symbol == AST_PARENTHESESES)
		status = execute_parentheses(cur->right_child);
	else
		status = execute_compound(cur->right_child);
	return (redirection_return(red_in, red_out, status));
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
