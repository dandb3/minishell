/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:55:16 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/20 13:53:34 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	do_builtin(char **cmds)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (*cmds == NULL)
		return (FAILURE);
	if (!ft_strcmp(*cmds, "cd"))
		exit_code = builtin_cd(cmds);
	else if (!ft_strcmp(*cmds, "echo"))
		builtin_echo(cmds);
	else if (!ft_strcmp(*cmds, "pwd"))
		exit_code = builtin_pwd();
	else if (!ft_strcmp(*cmds, "exit"))
		builtin_exit(cmds);
	else if (!ft_strcmp(*cmds, "export"))
		exit_code = builtin_export(cmds);
	else if (!ft_strcmp(*cmds, "unset"))
		exit_code = builtin_unset(cmds);
	else if (!ft_strcmp(*cmds, "env"))
		exit_code = builtin_env(cmds);
	else
		return (FAILURE);
	return (set_exitcode(exit_code, SUCCESS));
}
