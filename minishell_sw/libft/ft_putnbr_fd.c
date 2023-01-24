/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:37:22 by sunwsong          #+#    #+#             */
/*   Updated: 2022/11/18 15:50:59 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	const char	ch = n % 10 + '0';

	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n > 0 && n / 10 == 0)
		ft_putchar_fd(ch, fd);
	else
	{
		if (n != 0)
			ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(ch, fd);
	}
}
