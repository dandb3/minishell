/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:59:45 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/19 13:19:32 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../minishell.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>

# define HOME_NOT_SET "MINI: cd: HOME not set\n"

int		builtin_pwd(void);
int		builtin_cd(char **cmds);
void	builtin_echo(char **strs);
int		builtin_export(char **cmds);
void	builtin_exit(char **cmds);
int		builtin_unset(char **cmds);
int		builtin_env(char **cmds);

#endif