/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:59:29 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/14 17:14:30 by sunwsong         ###   ########.fr       */
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

typedef struct s_redir_fds
{
	int	in_fd;
	int	out_fd;
	int	append_fd;
	int	heredoc_fd;
}	t_redir_fds;

// execute_utils
char		**compound_to_char_twoptr(t_list *list);

// execute_pipe
t_pipe_info	*init_pipeinfo(t_tree *cur);

// redirect
int			manage_redirect(t_tree *cur, t_redir_fds *red_info);
int			close_redirect(t_redir_fds *red_info, t_symbol symbol, int new_fd);

// open_file
int			read_file(char *filename);
int			write_file(char *filename);
int			append_file(char *filename);

// here_doc
int			here_doc(char *word, int to_del);

#endif