/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:59:45 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/06 14:53:10 by sunwsong         ###   ########.fr       */
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

int		builtin_pwd(void);
int		builtin_cd(char **cmds, t_list **env_list);
void	builtin_echo(char **strs);
int		builtin_export(char **cmds, t_list **env_list);
void	builtin_exit(char **cmds);
int		builtin_unset(char **cmds, t_list **env_list);
int		builtin_env(char **cmds, t_list **env_list);

#endif