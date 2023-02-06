/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:55:16 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/06 15:13:15 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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
	return (1);
}
