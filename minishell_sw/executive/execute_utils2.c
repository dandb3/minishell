/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 21:24:06 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/18 11:11:42 by jdoh             ###   ########.fr       */
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
	return (tmp);
}

static void	find_path(char **cmd, char **path_split)
{
	char	**tmp;
	char	*merged_path;

	if (path_split == NULL)
		return ;
	tmp = path_split;
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
				free_twoptr(tmp, 0);
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
	if (path_split == NULL)
		return ;
	if (ft_strchr(cmd[0], '/') != NULL)
		access_check(cmd[0], '/');
	else
	{
		find_path(cmd, path_split);
		access_check(cmd[0], '\0');
	}
}

void	merge_wild(t_node *prev_token, t_node *cur_token, size_t len1)
{
	size_t	len2;
	size_t	idx;
	char	*str1;
	char	*str2;
	char	*merged_word;

	str1 = (char *)(prev_token->val);
	str2 = (char *)(cur_token->val);
	len2 = 0;
	if (str2)
		len2 = ft_strlen(str2);
	merged_word = (char *)ft_calloc(len1 + len2 + 1, sizeof(char));
	idx = -1;
	while (++idx < len1)
		merged_word[idx] = str1[idx];
	idx = -1;
	while (++idx < len2)
		merged_word[len1 + idx] = str2[idx];
	free(cur_token->val);
	cur_token->val = merged_word;
	del_node(prev_token, LEX);
}
