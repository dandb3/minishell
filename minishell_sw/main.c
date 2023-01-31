/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:32:49 by sunwsong          #+#    #+#             */
/*   Updated: 2023/01/31 16:37:52 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **envp)
{
	t_list	*env_list;

	atexit(leaks);
	(void) ac;
	(void) av;
	ft_signal();
	(void) envp;
	env_list = make_envlist(envp);
	prompt(env_list);
	return (0);
}
