/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:15:42 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/05 14:44:09 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include "minishell.h"

int	ft_terminal(void)
{
	struct termios	cur_termios;

	tcgetattr(0, &cur_termios);
	cur_termios.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &cur_termios);
	return (0);
}
