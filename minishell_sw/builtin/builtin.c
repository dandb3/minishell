/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:55:16 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/09 16:24:53 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static short	set_exitcode(int exit_code, t_list **env_list)
{
	char	*code;

	code = ft_itoa(exit_code);
	if (!code)
		exit(MALLOC_FAILURE);
	free(((t_env *)(*env_list)->head->next->val)->val);
	((t_env *)(*env_list)->head->next->val)->val = code;
	return (1);
}

int	do_builtin(char **cmds, t_list **env_list)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (!ft_strcmp(*cmds, "cd"))
		exit_code = builtin_cd(cmds, env_list);
	else if (!ft_strcmp(*cmds, "echo"))
		builtin_echo(cmds);
	else if (!ft_strcmp(*cmds, "pwd"))
		exit_code = builtin_pwd();
	else if (!ft_strcmp(*cmds, "exit"))
		builtin_exit(cmds);
	else if (!ft_strcmp(*cmds, "export"))
		exit_code = builtin_export(cmds, env_list);
	else if (!ft_strcmp(*cmds, "unset"))
		exit_code = builtin_unset(cmds, env_list);
	else if (!ft_strcmp(*cmds, "env"))
		exit_code = builtin_env(cmds, env_list);
	else
		return (0);
	return (set_exitcode(exit_code, env_list));
}
