/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:15:42 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/25 13:03:43 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include "minishell_bonus.h"

int	ft_terminal(void)
{
	struct termios	cur_termios;

	if (tcgetattr(0, &cur_termios) == -1)
		exit(EXIT_FAILURE);
	cur_termios.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, TCSANOW, &cur_termios) == -1)
		exit(EXIT_FAILURE);
	return (0);
}
