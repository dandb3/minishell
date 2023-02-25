/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:55:16 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/25 13:03:43 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_bonus.h"

int	do_builtin(char **cmd)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (*cmd == NULL)
		return (FAILURE);
	if (!ft_strcmp(*cmd, "cd"))
		exit_code = builtin_cd(cmd);
	else if (!ft_strcmp(*cmd, "echo"))
		builtin_echo(cmd);
	else if (!ft_strcmp(*cmd, "pwd"))
		exit_code = builtin_pwd();
	else if (!ft_strcmp(*cmd, "exit"))
		builtin_exit(cmd);
	else if (!ft_strcmp(*cmd, "export"))
		exit_code = builtin_export(cmd);
	else if (!ft_strcmp(*cmd, "unset"))
		exit_code = builtin_unset(cmd);
	else if (!ft_strcmp(*cmd, "env"))
		exit_code = builtin_env(cmd);
	else
		return (FAILURE);
	return (set_exitcode(exit_code, SUCCESS));
}
