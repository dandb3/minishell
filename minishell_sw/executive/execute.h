/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:59:29 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/11 19:39:13 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../minishell.h"
# include "../new_parser/parser.h"
# include <sys/wait.h>

typedef struct s_pipe_info
{
	char	***cmds;
	int		(*fds)[2];
	int		process_cnt;
}	t_pipe_info;

void	perror_msg(char *msg, int exit_status);
void	error_msg(char *msg, int exit_status);

int		get_next_line(int fd, char **result);
void	read_file(char *filename);
void	write_file(char *filename);
void	append_file(char *filename);

#endif