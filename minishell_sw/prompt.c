/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:41:06 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/02 11:14:07 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int	prompt(t_list *env_list)
{
	char	*cmd;
	char	**cmds;

	system("clear"); // 지우세용
	while (1)
	{
		cmd = readline("MINI$ ");
		if (!cmd)
		{
			ft_printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		if (ft_strlen(cmd))
		{
			add_history(cmd);
			cmds = ft_split(cmd, ' ');
			if (!cmds)
				exit(MALLOC_FAILURE);
			if (*cmds)
				do_builtin(cmds, &env_list);
			free_twoptr(cmds, 0);
		}
		free(cmd);
	}
	clear_history();
	return (0);
}
