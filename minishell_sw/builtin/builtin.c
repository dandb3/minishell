/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:55:16 by sunwsong          #+#    #+#             */
/*   Updated: 2023/01/30 13:58:10 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	do_builtin(char **cmds, t_list **env_list)
{
	if (!ft_strncmp(*cmds, "cd", 2))
		builtin_cd(cmds);
	else if (!ft_strncmp(*cmds, "echo", 4))
		builtin_echo(cmds);
	else if (!ft_strncmp(*cmds, "pwd", 3))
		builtin_pwd();
	else if (!ft_strncmp(*cmds, "exit", 4))
		builtin_exit(cmds);
	else if (!ft_strncmp(*cmds, "export", 6))
		builtin_export(cmds, env_list);
	else if (!ft_strncmp(*cmds, "unset", 5))
		builtin_unset(cmds, env_list);
	else if (!ft_strncmp(*cmds, "env", 3))
		builtin_env(env_list);
	else
		return (0);
	return (1);
}
