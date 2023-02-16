/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:44:19 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/15 13:13:00 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	make_here_doc_tmp_file(char *word, int open_fd)
{
	size_t	idx;
	size_t	prev;
	size_t	envlen;
	char	*key;
	char	*val;

	prev = 0;
	idx = -1;
	while (word[++idx])
	{
		if (word[idx] == '$')
		{
			write(open_fd, word + prev, idx - prev);
			envlen = get_envlen(word + idx + 1);
			key = ft_substr(word + idx + 1, 0, envlen);
			if (!key)
				exit(MALLOC_FAILURE);
			val = find_env_val(key);
			if (val)
				write(open_fd, val, ft_strlen(val));
			free_ret(key, val, NULL, 0);
			prev = idx + envlen + 1;
		}
	}
	write(open_fd, word + prev, idx - prev + 1);
}

static int	del_here_doc(const char *tmp_dir, int *file_num)
{
	char	*file_num_to_a;
	char	*tmp_file;
	int		idx;

	idx = -1;
	while (++idx < *file_num)
	{
		file_num_to_a = ft_itoa(idx);
		if (!file_num_to_a)
			exit(MALLOC_FAILURE);
		tmp_file = ft_strjoin(tmp_dir, file_num_to_a);
		free(file_num_to_a);
		if (!tmp_file)
			exit(MALLOC_FAILURE);
		unlink(tmp_file);
		free(tmp_file);
	}
	*file_num = 0;
	return (SUCCESS);
}

int	here_doc(char *word, int to_del)
{
	const char	*tmp_dir = "/tmp/";
	char		*file_num_to_a;
	char		*tmp_file;
	static int	file_num;
	int			open_fd;

	if (to_del)
		return (del_here_doc(tmp_dir, &file_num));
	file_num_to_a = ft_itoa(file_num++);
	if (!file_num_to_a)
		exit(MALLOC_FAILURE);
	tmp_file = ft_strjoin(tmp_dir, file_num_to_a);
	if (tmp_file == NULL)
		exit(MALLOC_FAILURE);
	open_fd = open(tmp_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (open_fd < 0)
		perror_msg(tmp_file, 1);
	make_here_doc_tmp_file(word, open_fd);
	if (close(open_fd) < 0)
		perror_msg(NULL, 1);
	read_file(tmp_file);
	return (free_ret(file_num_to_a, tmp_file, NULL, SUCCESS));
}
