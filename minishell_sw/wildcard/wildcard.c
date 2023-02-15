/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:07:45 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/15 15:12:06 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char	*check_list_names(char *wstr, t_list *file_list)
{
	t_wild	wild;
	char	**dp;
	char	*res;

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

char	*wildcard(char *wstr)
{
	DIR				*dir_ptr;
	t_list			*file_list;
	const char		*path = getcwd(NULL, UINT32_MAX);

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
	return (check_list_names(wstr, file_list));
}
