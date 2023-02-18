/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:59:29 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/18 20:02:17 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../minishell.h"
# include "../new_parser/parser.h"
# include <sys/wait.h>

# define COMMAND_NOT_FOUND "command not found\n"

typedef struct s_pipe_info
{
	pid_t	*pid_table;
	char	**path_split;
	int		(*fds)[2];
	int		process_cnt;
}	t_pipe_info;

// execute_utils
char		**compound_to_char_twoptr(t_tree *cur);
char		*expand_char(t_list *compound_list);
void		add_path_and_access_check(char **path_split, char **cmd);
char		**make_path_split(void);
void		merge_wild(t_node *prev_token, t_node *cur_token, size_t len1);

// execute_pipe
void		init_pipeinfo(t_pipe_info *info, t_tree *cur);
void		pipe_process(t_pipe_info *info, t_tree *cur_tree);

// redirect
void		manage_redirect(t_tree *cur);

// open_file
void		read_file(char *filename);
void		write_file(char *filename);
void		append_file(char *filename);

// here_doc
void		here_doc(char *word, int to_del);

#endif