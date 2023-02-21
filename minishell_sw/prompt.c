/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:41:06 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/21 20:28:45 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	eof_exit(void)
{
	printf("exit\n");
	exit(get_exitcode());
}

int	prompt(void)
{
	char	*cmd;
	t_tree	*parse_tree;

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
				free_tree(parse_tree);
			}
		}
		free(cmd);
	}
	clear_history();
	return (0);
}
