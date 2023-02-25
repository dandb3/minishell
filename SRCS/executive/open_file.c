/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:47:12 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/18 19:30:22 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	read_file(char *filename)
{
	int	open_fd;

	open_fd = open(filename, O_RDONLY);
	if (open_fd < 0)
	{
		write(STDERR_FILENO, SHELL, SHELL_LEN);
		perror(filename);
		return (1);
	}
	if (dup2(open_fd, STDIN_FILENO) < 0)
		perror_msg(NULL, 1);
	if (close(open_fd) < 0)
		perror_msg(NULL, 1);
	return (SUCCESS);
}

int	write_file(char *filename)
{
	int	open_fd;

	open_fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (open_fd < 0)
	{
		write(STDERR_FILENO, SHELL, SHELL_LEN);
		perror(filename);
		return (1);
	}
	if (dup2(open_fd, STDOUT_FILENO) < 0)
		perror_msg(NULL, 1);
	if (close(open_fd) < 0)
		perror_msg(NULL, 1);
	return (SUCCESS);
}

int	append_file(char *filename)
{
	int	open_fd;

	open_fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (open_fd < 0)
	{
		write(STDERR_FILENO, SHELL, SHELL_LEN);
		perror(filename);
		return (1);
	}
	if (dup2(open_fd, STDOUT_FILENO) < 0)
		perror_msg(NULL, 1);
	if (close(open_fd) < 0)
		perror_msg(NULL, 1);
	return (SUCCESS);
}
