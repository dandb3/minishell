/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:07:45 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/06 21:11:20 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

char	disc(t_wild *wild, char **dp, size_t widx, size_t nidx)
{
	printf("1\n");
	if (widx < wild->wlen && nidx < wild->nlen \
		&& dp[widx][nidx] != -1)
		return (dp[widx][nidx]);
	printf("2\n");
	if (widx < wild->wlen && nidx < wild->nlen \
		&& wild->wstr[widx] == wild->name[nidx])
		return (dp[widx][nidx] \
			= disc(wild, dp, widx + 1, nidx + 1));
	printf("3\n");
	if (widx == wild->wlen)
	{
		printf("3.5\n");
		if (nidx == wild->nlen)
			return (1);
		printf("%zu %zu\n", widx, nidx);
		return (0);
	}
	printf("4\n");
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
	while (dp[++idx])
		free(dp[idx]);
	idx = -1;
	while (++idx < wild->wlen)
	{
		dp[idx] = (char *)malloc(sizeof(char) * wild->nlen);
		if (!dp[idx])
			exit(MALLOC_FAILURE);
		ft_memset(dp[idx], -1, sizeof(char) * wild->nlen);
		ft_printf("%d: %d\n", idx, dp[idx][0]);
	}
	dp[idx] = NULL;
}

void	check_names(char *wstr, t_list *file_list)
{
	t_wild	wild;
	t_node	*cur;
	char	**dp;

	wild.wstr = wstr;
	wild.wlen = ft_strlen(wstr);
	dp = (char **)ft_calloc(wild.wlen + 1, sizeof(char *));
	if (!dp)
		exit(MALLOC_FAILURE);
	cur = file_list->head->next;
	while (cur->next)
	{
		wild.name = (char *)(cur->val);
		wild.nlen = ft_strlen(wild.name);
		free_and_realloc(&wild, dp);
		printf("disc start\n");
		if (disc(&wild, dp, 0, 0))
			printf("matched: %s\n", wild.name);
		cur = cur->next;
	}
	free_list(file_list, 0, NAME);
}

int	wildcard(char *wstr, char *path)
{
	DIR				*dir_ptr;
	t_list			*file_list;
	struct dirent	*file;
	char			*file_name;

	dir_ptr = opendir(path);
	if (!dir_ptr)
		return (FAILURE);
	file_list = make_list(NAME);
	while (1)
	{
		file = readdir(dir_ptr);
		if (!file)
			break ;
		file_name = ft_strdup(file->d_name);
		if (!file_name)
			exit(MALLOC_FAILURE);
		push_node(make_node(file_name, -1), file_list);
	}
	closedir(dir_ptr);
	sort_list(file_list);
	check_names(wstr, file_list);
	return (free_list(file_list, SUCCESS, NAME));
}
