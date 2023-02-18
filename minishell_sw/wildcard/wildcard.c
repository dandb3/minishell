/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:07:45 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/18 13:08:05 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	print_wild(t_wild *wild) // 지우세용
{
	printf("wild->wstr: %s\n", wild->wstr);
	printf("wild->name: %s\n", wild->name);
	printf("wild->wlen: %zu\n", wild->wlen);
	printf("wild->nlen: %zu\n", wild->nlen);
}

static char	*iterate_list(char **dp, t_wild *wild, t_list *file_list)
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
		wild->name = cur->val;
		wild->nlen = ft_strlen(wild->name);
		free_and_realloc_dp(wild, dp);
		if (disc(wild, dp, 0, 0))
		{
			res = ft_strjoin_and_free(res, wild->name);
			res = ft_strjoin_and_free(res, " ");
		}
		cur = cur->next;
	}
	return (res);
}

static char	*check_list_names(char *wstr, size_t wlen, t_list *file_list)
{
	t_wild	wild;
	char	**dp;
	char	*res;

	wild.wstr = wilddup(wstr, wlen);
	wild.wlen = wlen;
	dp = (char **)ft_calloc(wild.wlen + 1, sizeof(char *));
	if (!dp)
		exit(MALLOC_FAILURE);
	res = iterate_list(dp, &wild, file_list);
	free(wild.wstr);
	free_twoptr(dp, 0);
	return (res);
}

static void	set_file_list(DIR *dir_ptr, t_list **file_list)
{
	struct dirent	*file;
	char			*file_name;

	while (1)
	{
		file = readdir(dir_ptr);
		if (!file)
			return ;
		if (!ft_strncmp(file->d_name, ".", 1))
			continue ;
		file_name = ft_strdup(file->d_name);
		if (!file_name)
			exit(MALLOC_FAILURE);
		push_node(make_node(file_name, -1), *file_list);
	}
}

char	*wildcard(char *wstr, size_t wlen)
{
	DIR		*dir_ptr;
	t_list	*file_list;
	char	*path;
	char	*res;

	path = getcwd(NULL, UINT32_MAX);
	if (!path)
		exit(EXIT_FAILURE);
	dir_ptr = opendir(path);
	free(path);
	if (!dir_ptr)
		return (NULL);
	file_list = make_list(NAME);
	set_file_list(dir_ptr, &file_list);
	sort_list(file_list);
	closedir(dir_ptr);
	res = check_list_names(wstr, wlen, file_list);
	free_list(file_list, 0, NAME);
	return (res);
}
