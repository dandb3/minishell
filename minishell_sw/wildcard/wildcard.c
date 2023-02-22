/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:07:45 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/21 20:39:10 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

static t_list	*iterate_list(char **dp, t_wild *wild, t_list *file_list)
{
	t_node	*cur;
	t_list	*res;
	char	*str;

	res = make_list(NAME);
	cur = file_list->head->next;
	while (cur->next)
	{
		wild->name = cur->val;
		wild->nlen = ft_strlen(wild->name);
		free_and_realloc_dp(wild, dp);
		if (disc(wild, dp, 0, 0))
		{
			str = ft_strdup(wild->name);
			if (str == NULL)
				exit(MALLOC_FAILURE);
			push_node(make_node(str, -1), res);
		}
		cur = cur->next;
	}
	return (res);
}

static t_list	*check_list_names(char *wstr, size_t wlen, t_list *file_list)
{
	t_wild	wild;
	char	**dp;
	t_list	*res;

	wild.wstr = wstr;
	wild.wlen = wlen;
	dp = (char **)ft_calloc(wild.wlen + 1, sizeof(char *));
	if (!dp)
		exit(MALLOC_FAILURE);
	res = iterate_list(dp, &wild, file_list);
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

t_list	*wildcard(char *wstr, size_t wlen)
{
	DIR		*dir_ptr;
	t_list	*file_list;
	t_list	*res;
	char	*path;

	path = ft_getcwd(NULL);
	if (!path)
		return ((t_list *)set_exitcode(1, 0));
	dir_ptr = opendir(path);
	free(path);
	if (!dir_ptr)
		return ((t_list *)set_exitcode(1, 0));
	file_list = make_list(NAME);
	set_file_list(dir_ptr, &file_list);
	sort_list(file_list);
	closedir(dir_ptr);
	res = check_list_names(wstr, wlen, file_list);
	free_list(file_list, 0, NAME);
	if (res->size == 0)
		push_wstr(res, wstr, wlen);
	return (res);
}
