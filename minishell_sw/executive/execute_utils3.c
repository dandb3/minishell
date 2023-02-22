/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:41:39 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/21 20:52:07 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	get_status(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		perror_msg(NULL, 1);
	if ((status & 0xff) == 0)
		return ((status >> 8) & 0xff);
	if ((status & 0xff) != 0xff && (status & 0xff) != 0)
		return (128 + (status & 0xff));
	return (status >> 8);
}

int	redirection_return(int red_in, int red_out, int ret)
{
	if (dup2(red_in, STDIN_FILENO) == FAILURE)
		perror_msg(NULL, 1);
	if (dup2(red_out, STDOUT_FILENO) == FAILURE)
		perror_msg(NULL, 1);
	if (close(red_in) == FAILURE)
		perror_msg(NULL, 1);
	if (close(red_out) == FAILURE)
		perror_msg(NULL, 1);
	return (ret);
}

void	redirection_set(int *red_in, int *red_out)
{
	*red_in = dup(STDIN_FILENO);
	*red_out = dup(STDOUT_FILENO);
	if (*red_in == FAILURE || *red_out == FAILURE)
		perror_msg(NULL, 1);
}
