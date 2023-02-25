/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:41:06 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/25 13:03:43 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	eof_exit(void)
{
	write(STDOUT_FILENO, "exit\n", 5);
	clear_history();
	exit(get_exitcode());
}

static int	redirection_return(int red_in, int red_out, int ret)
{
	if (dup2(red_in, STDIN_FILENO) == FAILURE)
		perror_msg(NULL, 1);
	if (dup2(red_out, STDOUT_FILENO) == FAILURE)
		perror_msg(NULL, 1);
	return (ret);
}

static void	redirection_set(int *red_in, int *red_out)
{
	*red_in = dup(STDIN_FILENO);
	*red_out = dup(STDOUT_FILENO);
	if (*red_in == FAILURE || *red_out == FAILURE)
		perror_msg(NULL, 1);
}

void	prompt(void)
{
	char	*cmd;
	t_tree	*parse_tree;
	int		red_in;
	int		red_out;

	redirection_set(&red_in, &red_out);
	while (1)
	{
		cmd = readline("MINI$ ");
		if (!cmd)
			eof_exit();
		if (ft_strlen(cmd))
		{
			add_history(cmd);
			parse_tree = parser(cmd);
			if (parse_tree)
			{
				set_exitcode(execute(parse_tree, 0), 0);
				redirection_return(red_in, red_out, 0);
				free_tree(parse_tree);
			}
		}
		free(cmd);
	}
	clear_history();
}
