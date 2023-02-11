/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:07:45 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/07 19:54:16 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

char	disc(t_wild *wild, char **dp, size_t widx, size_t nidx)
{
	if (widx < wild->wlen && nidx < wild->nlen \
		&& dp[widx][nidx] != -1)
		return (dp[widx][nidx]);
	if (widx < wild->wlen && nidx < wild->nlen \
		&& wild->wstr[widx] == wild->name[nidx])
		return (dp[widx][nidx] \
			= disc(wild, dp, widx + 1, nidx + 1));
	if (widx == wild->wlen)
	{
		if (nidx == wild->nlen)
			return (1);
		return (0);
	}
	if (wild->wstr[widx] == '*')
		if (disc(wild, dp, widx + 1, nidx)
			|| (nidx < wild->nlen && disc(wild, dp, widx, nidx + 1)))
			return (dp[widx][nidx] = 1);
	return (dp[widx][nidx] = 0);
}

void	free_and_realloc(t_wild *wild, char **dp)
{
	size_t	idx;

	idx = -1;
	while (++idx < wild->wlen)
	{
		free(dp[idx]);
		dp[idx] = NULL;
	}
	idx = -1;
	while (++idx < wild->wlen)
	{
		dp[idx] = (char *)malloc(sizeof(char) * wild->nlen);
		if (!dp[idx])
			exit(MALLOC_FAILURE);
		ft_memset(dp[idx], -1, sizeof(char) * wild->nlen);
	}
}

char	*iterate_list(char **dp, t_wild *wild, t_list *file_list)
{
	t_node	*cur;
	char	*res;

	res = (char *)malloc(sizeof(char));
	if (!res)
		exit(MALLOC_FAILURE);
	*res = 0;
	cur = file_list->head->next;
	while (cur->next)
	{
		wild->name = (char *)(cur->val);
		wild->nlen = ft_strlen(wild->name);
		free_and_realloc(wild, dp);
		if (disc(wild, dp, 0, 0))
		{
			res = ft_strjoin_and_free(res, wild->name);
			res = ft_strjoin_and_free(res, " ");
		}
		cur = cur->next;
	}
	return (res);
}

char	*check_names(char *wstr, t_list *file_list)
{
	t_wild	wild;
	char	**dp;
	char	*res;

	sort_list(file_list);
	wild.wstr = wstr;
	wild.wlen = ft_strlen(wstr);
	dp = (char **)ft_calloc(wild.wlen + 1, sizeof(char *));
	if (!dp)
		exit(MALLOC_FAILURE);
	res = iterate_list(dp, &wild, file_list);
	free_twoptr(dp, 0);
	free_list(file_list, 0, NAME);
	return (res);
}

char	*wildcard(char *wstr, char *path)
{
	DIR				*dir_ptr;
	t_list			*file_list;
	struct dirent	*file;
	char			*file_name;

	dir_ptr = opendir(path);
	if (!dir_ptr)
		return (NULL);
	file_list = make_list(NAME);
	while (1)
	{
		file = readdir(dir_ptr);
		if (!file)
			break ;
		if (!ft_strncmp(file->d_name, ".", 1))
			continue ;
		file_name = ft_strdup(file->d_name);
		if (!file_name)
			exit(MALLOC_FAILURE);
		push_node(make_node(file_name, -1), file_list);
	}
	closedir(dir_ptr);
	return (check_names(wstr, file_list));
}
