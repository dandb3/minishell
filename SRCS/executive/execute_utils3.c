/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:41:39 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/24 10:55:10 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	get_status(pid_t pid)
{
	int	status;

	set_signal(SG_STOP);
	if (waitpid(pid, &status, 0) == -1)
	{
		set_signal(SG_RUN);
		perror_msg(NULL, 1);
	}
	set_signal(SG_RUN);
	if ((status & 0xff) == 0)
		return ((status >> 8) & 0xff);
	if ((status & 0xff) != 0xff && (status & 0xff) != 0)
	{
		if ((status & 0xff) == SIGINT)
			write(STDERR_FILENO, "^C\n", 3);
		else if ((status & 0xff) == SIGQUIT)
			write(STDERR_FILENO, "^\\Quit: 3\n", 10);
		return (128 + (status & 0xff));
	}
	return (status >> 8);
}
