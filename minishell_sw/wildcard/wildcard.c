/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:07:45 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/06 16:06:42 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <string.h>
#include "../minishell.h"

char	dp[1025][1025];

char	disc(char *wild, char *str, size_t wild_idx, size_t str_idx)
{
	const size_t	wild_len = strlen(wild);
	const size_t	str_len = strlen(str);

	if (dp[wild_idx][str_idx] != -1)
		return (dp[wild_idx][str_idx]);
	if (wild_idx < wild_len && str_idx < str_len \
		&& wild[wild_idx] == str[str_idx])
		return (dp[wild_idx][str_idx] \
			= disc(wild, str, wild_idx + 1, str_idx + 1));
	if (wild_idx == wild_len)
	{
		if (str_idx == str_len)
			return (dp[wild_idx][str_idx] = 1);
		return (dp[wild_idx][str_idx] = 0);
	}
	if (wild[wild_idx] == '*')
		if (disc(wild, str, wild_idx + 1, str_idx)
			|| (str_idx < str_len && disc(wild, str, wild_idx, str_idx + 1)))
			return (dp[wild_idx][str_idx] = 1);
	return (dp[wild_idx][str_idx] = 0);
}

// int	wildcard(char *wild)
// {
// 	DIR				*dir_ptr;
// 	t_list			*file_list;
// 	struct dirent	*file;
// 	char			*path;
// 	char			*file_name;

// 	dir_ptr = opendir(path);
// 	if (!dir_ptr)
// 		return (FAILURE);
// 	file_list = make_list(NAME);
// 	while (1)
// 	{
// 		file = readdir(dir_ptr);
// 		if (!file)
// 			break ;
// 		file_name = ft_strdup(file->d_name);
// 		if (!file_name)
// 			exit(MALLOC_FAILURE);
// 		push_node(make_node(file_name), -1);
// 	}
// 	closedir(dir_ptr);
// 	return (free_list(file_list, SUCCESS, NAME));
// }

#include <stdio.h>
int	main(int ac, char **av)
{
	(void) ac;
	memset(dp, -1, sizeof(dp));
	printf("%s %s\n", av[1], av[2]);
	if (disc(av[1], av[2], 0, 0))
		printf("GOOD\n");
	else
		printf("NO\n");
	return (0);
}
