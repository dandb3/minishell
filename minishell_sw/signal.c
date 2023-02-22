/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:28:13 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/22 17:21:51 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

static void	handler1(int sig)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	set_exitcode(1, SUCCESS);
	(void) sig;
}

void	set_signal(int mode)
{
	if (mode == SG_RUN)
	{
		signal(SIGINT, handler1);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == SG_STOP)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == SG_HEREDOC_PARENT) // ?
	{
		return ;
	}
	else if (mode == SG_HEREDOC_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		return ;
	}
	else if (mode == SG_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

int	ft_signal(void)
{
	struct sigaction	act_int;
	struct sigaction	act_quit;

	act_int.sa_flags = SA_RESTART;
	act_int.__sigaction_u.__sa_handler = handler1;
	act_quit.sa_flags = SA_RESTART;
	act_quit.__sigaction_u.__sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &act_int, NULL) | sigaction(SIGQUIT, &act_quit, NULL))
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	return (SUCCESS);
}
