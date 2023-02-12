/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:47:12 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/12 20:55:48 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	read_file(char *filename)
{
	int	open_fd;

	open_fd = open(filename, O_RDONLY);
	if (open_fd < 0)
		perror_msg(filename, 1);
	if (dup2(open_fd, STDIN_FILENO) < 0)
		perror_msg(NULL, 1);
	if (close(open_fd) < 0)
		perror_msg(NULL, 1);
}

void	write_file(char *filename)
{
	int	open_fd;

	open_fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (open_fd < 0)
		perror_msg(filename, 1);
	if (dup2(open_fd, STDOUT_FILENO) < 0)
		perror_msg(NULL, 1);
	if (close(open_fd) < 0)
		perror_msg(NULL, 1);
}

void	append_file(char *filename)
{
	int	open_fd;

	open_fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (open_fd < 0)
		perror_msg(filename, 1);
	if (dup2(open_fd, STDOUT_FILENO) < 0)
		perror_msg(NULL, 1);
	if (close(open_fd) < 0)
		perror_msg(NULL, 1);
}

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

void	here_doc(char *word, t_list **lst, int fd_stdin)
{
	const char	*tmp_dir = "/tmp/";
	char		*tmp_file;
	static int	file_num;
	int			open_fd;

	tmp_file = ft_strjoin(tmp_dir, file_num++);
	if (tmp_file == NULL)
		exit(MALLOC_FAILURE);
	open_fd = open(tmp_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (open_fd < 0)
		perror_msg(tmp_file, 1);
	input_here_doc(word, tmp_file, fd_stdin, open_fd);
	if (close(open_fd) < 0)
		perror_msg(NULL, 1);
	read_file(tmp_file);
	free(tmp_file);
}
