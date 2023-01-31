/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:41:06 by sunwsong          #+#    #+#             */
/*   Updated: 2023/01/30 15:23:16 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int	prompt(__attribute__((unused)) t_list *env_list)
{
	char	*cmd;
	char	**cmds;

	system("clear");
	rl_line_buffer = "hihi";
	while (1)
	{
		cmd = readline("MINI$ ");
		if (!cmd)
			return (0);
		if (ft_strlen(cmd) == 0)
		{
			free(cmd);
			continue ;
		}
		add_history(cmd);
		cmds = ft_split(cmd, ' ');
		if (!cmds)
			exit(MALLOC_FAILURE);
		if (*cmds)
			do_builtin(cmds, &env_list);
		free_twoptr(cmds, 0);
	}
	clear_history();
	return (0);
}
