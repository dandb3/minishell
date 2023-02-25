/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:59:45 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/25 11:34:45 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../minishell.h"
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>

# define HOME_NOT_SET "MINI: cd: HOME not set\n"

int		builtin_pwd(void);
int		builtin_cd(char **cmd);
void	builtin_echo(char **strs);
int		builtin_export(char **cmd);
void	builtin_exit(char **cmd);
int		builtin_unset(char **cmd);
int		builtin_env(char **cmd);

#endif