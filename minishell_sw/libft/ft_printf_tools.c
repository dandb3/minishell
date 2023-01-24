/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:53:44 by sunwsong          #+#    #+#             */
/*   Updated: 2022/12/27 18:05:50 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_printf_char(int ch)
{
	char	c;

	c = (char)ch;
	if (write(1, &ch, 1) != 1)
		return (-1);
	return (1);
}

long long	ft_printf_string(char *str)
{
	long long	len;

	if (str == 0)
	{
		if (write(1, "(null)", 6) != 6)
			return (-1);
		return (6);
	}
	len = ft_strlen(str);
	if (write(1, str, len) != len)
		return (-1);
	return (len);
}

long long	ft_printf_nbr(int num)
{
	return (ft_putnbr_base((long long)num, 10, "0123456789"));
}

long long	ft_printf_unbr(unsigned int num)
{
	return (ft_putnbr_base((long long)num, 10, "0123456789"));
}

long long	ft_printf_hex(unsigned int num, int is_upper)
{
	if (is_upper)
		return (ft_putnbr_base(num, 16, "0123456789ABCDEF"));
	else
		return (ft_putnbr_base(num, 16, "0123456789abcdef"));
}
