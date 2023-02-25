/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:59:45 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/25 13:03:43 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_BONUS_H
# define BUILTIN_BONUS_H

# include "../minishell_bonus.h"
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