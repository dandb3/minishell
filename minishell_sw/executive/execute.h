/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:59:29 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/12 13:07:10 by sunwsong         ###   ########.fr       */
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

// execute_utils
char		**compound_to_char_twoptr(t_list *list);

// execute_pipe
t_pipe_info	*init_pipeinfo(t_tree *cur);

// redirect
int			manage_redirect(t_tree *cur);

// open_file
void		read_file(char *filename);
void		write_file(char *filename);
void		append_file(char *filename);

#endif