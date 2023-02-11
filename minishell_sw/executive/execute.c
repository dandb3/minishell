/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:11:30 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/11 20:14:03 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	execute_pipe(t_tree *cur)
{
	t_pipe_info	info;

	info = init_pipeinfo(cur);
	return (pipe_process(info));
}

int	execute_parentheses(t_tree *cur)
{
	const pid_t	pid = fork();
	int			status;

	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid != 0)
	{
		waitpid(pid, NULL, NULL);
	}
	else
	{
		execute(cur->left_child);
	}
}

int	execute_compound(t_tree *cur)
{
	
}

int	execute(t_tree *cur, int prev_status)
{
	int	status;

	if (!cur)
		return (prev_status);
	if (cur->symbol == AST_PIPE)
		status = execute_pipe(cur);
	else if (cur->symbol == AST_AND)
	{
		status = execute(cur->left_child, 0);
		if (!status)
			status = execute(cur->right_child, status);
	}
	else if (cur->symbol == AST_OR)
	{
		status = execute(cur->left_child, 0);
		if (status)
			status = execute(cur->right_child, status);
	}
	else if (cur->symbol == AST_PARENTHESESES)
		status = execute_parentheses(cur, 0);
	else if (cur->symbol == AST_COMPOUND)
		status = execute_compound(cur, 0);
	return (status);
}
