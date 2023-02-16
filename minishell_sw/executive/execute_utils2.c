/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 21:24:06 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/16 21:51:19 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static char	*strjoin_slash(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, "/");
	if (tmp == NULL)
		exit(MALLOC_FAILURE);
	tmp = ft_strjoin_and_free(tmp, s2);
	if (tmp == NULL)
		exit(MALLOC_FAILURE);
	return (tmp);
}

static void	find_path(char **cmd, char **path_split)
{
	char	*merged_path;

	if (path_split == NULL)
		return ;
	while (*path_split)
	{
		merged_path = strjoin_slash(*path_split, cmd[0]);
		if (access(merged_path, F_OK) == SUCCESS)
		{
			free(cmd[0]);
			cmd[0] = merged_path;
			merged_path = NULL;
			if (access(cmd[0], X_OK) == SUCCESS)
			{
				free_twoptr(path_split, 0);
				return ;
			}
		}
		free(merged_path);
		++path_split;
	}
}

static void	access_check(char *cmd, char mode)
{
	if (access(cmd, F_OK) == FAILURE)
	{
		write(STDERR_FILENO, SHELL, SHELL_LEN);
		if (mode == '/')
			perror_msg(cmd, 127);
		else
		{
			write(STDERR_FILENO, cmd, ft_strlen(cmd));
			write(STDERR_FILENO, ": ", 2);
			error_msg(COMMAND_NOT_FOUND, 127);
		}
	}
	else if (access(cmd, X_OK) == FAILURE)
	{
		write(STDERR_FILENO, SHELL, SHELL_LEN);
		perror_msg(cmd, 126);
	}
}

void	add_path_and_access_check(char **path_split, char **cmd)
{
	if (ft_strchr(cmd[0], '/') != NULL)
		access_check(cmd[0], '/');
	else
	{
		find_path(cmd, path_split);
		access_check(cmd[0], '\0');
	}
}
