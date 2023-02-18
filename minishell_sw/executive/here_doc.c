/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:44:19 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/18 20:35:38 by jdoh             ###   ########seoul.kr  */
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
	static int	file_num;
	char		*file_num_to_a;
	char		*tmp_file;
	int			open_fd;
	int			status;

	if (to_del)
		return (del_here_doc("/tmp/", &file_num));
	file_num_to_a = ft_itoa(file_num++);
	tmp_file = ft_strjoin("/tmp/", file_num_to_a);
	if (tmp_file == NULL || file_num_to_a == NULL)
		exit(MALLOC_FAILURE);
	open_fd = open(tmp_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (open_fd < 0)
		perror_msg(tmp_file, 1);
	make_here_doc_tmp_file(word, open_fd);
	if (close(open_fd) < 0)
		perror_msg(NULL, 1);
	status = read_file(tmp_file);
	free_ret(file_num_to_a, tmp_file, NULL, SUCCESS);
	return (status);
}
