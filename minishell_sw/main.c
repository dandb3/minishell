/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:32:49 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/21 20:31:24 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	extern char	**environ;

	(void) av;
	if (ac != 1)
	{
		write(STDERR_FILENO, "There should be no argument\n", 28);
		return (1);
	}
	g_env_list = make_envlist(environ);
	ft_signal();
	ft_terminal();
	prompt();
	return (0);
}

//rl_catch_signals = 0;