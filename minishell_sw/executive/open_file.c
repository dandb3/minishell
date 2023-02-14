/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:47:12 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/14 16:43:47 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	read_file(char *filename)
{
	int	open_fd;

	if (!filename)
		return ;
	open_fd = open(filename, O_RDONLY);
	if (open_fd < 0)
		perror_msg(filename, 1);
	if (dup2(open_fd, STDIN_FILENO) < 0)
		perror_msg(NULL, 1);
	if (close(open_fd) < 0)
		perror_msg(NULL, 1);
	return (open_fd);
}

int	write_file(char *filename)
{
	int	open_fd;

	open_fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (open_fd < 0)
		perror_msg(filename, 1);
	if (dup2(open_fd, STDOUT_FILENO) < 0)
		perror_msg(NULL, 1);
	if (close(open_fd) < 0)
		perror_msg(NULL, 1);
	return (open_fd);
}

int	append_file(char *filename)
{
	int	open_fd;

	open_fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (open_fd < 0)
		perror_msg(filename, 1);
	if (dup2(open_fd, STDOUT_FILENO) < 0)
		perror_msg(NULL, 1);
	if (close(open_fd) < 0)
		perror_msg(NULL, 1);
	return (open_fd);
}
