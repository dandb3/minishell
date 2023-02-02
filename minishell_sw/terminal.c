/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:15:42 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/01 13:45:51 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include "minishell.h"

int	terminal(void)
{
	struct termios	termios_p;

	printf("%d\n", tcgetattr(0, &termios_p));
	return (0);
}
