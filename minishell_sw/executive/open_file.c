/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:47:12 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/11 19:39:24 by sunwsong         ###   ########.fr       */
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

static void	input_here_doc(char *word, char *tmp_file,
	int fd_stdin, int open_fd)
{
	char	*read_line;
	int		status;

	while (status > 0)
	{
		if (!ft_strncmp(word, read_line, ft_strlen(word))
			&& read_line[ft_strlen(word)] == '\n')
		{
			free(read_line);
			break ;
		}
		if (write(open_fd, read_line, ft_strlen(read_line)) < 0)
		{
			free(read_line);
			perror_msg(NULL, 1);
		}
		free(read_line);
		status = get_next_line(fd_stdin, &read_line);
	}
	if (status == -1)
		perror_msg(NULL, 1);
}

void	here_doc(char *word, t_list **lst, int fd_stdin)
{
	const char	*tmp_dir = "/tmp/";
	int			open_fd;
	char		*tmp_file;

	tmp_file = ft_strjoin(tmp_dir, word);
	if (tmp_file == NULL)
		perror_msg(NULL, 1);
	open_fd = open(tmp_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (open_fd < 0)
		perror_msg(tmp_file, 1);
	input_here_doc(word, tmp_file, fd_stdin, open_fd);
	if (close(open_fd) < 0)
		perror_msg(NULL, 1);
	read_file(tmp_file);
	free(tmp_file);
}
