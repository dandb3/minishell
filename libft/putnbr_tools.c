/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:07:42 by sunwsong          #+#    #+#             */
/*   Updated: 2022/12/16 16:27:18 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	print_num_base(size_t num, int len, const char *base, long long *cnt)
{
	if (num == 0)
		return (1);
	(*cnt)++;
	if (!print_num_base(num / len, len, base, cnt))
		return (0);
	if (write(1, &base[num % len], 1) != 1)
		return (0);
	return (1);
}

long long	ft_putnbr_base(long long nbr, int len, const char *base)
{
	long long	cnt;
	size_t		num;

	cnt = 0;
	if (nbr == 0)
	{
		if (write(1, "0", 1) != 1)
			return (-1);
		return (1);
	}
	if (nbr > 0)
		num = (size_t)nbr;
	else
	{
		num = (size_t)(-nbr);
		if (write(1, "-", 1) != 1)
			return (-1);
		cnt++;
	}
	if (!print_num_base(num, len, base, &cnt))
		return (-1);
	return (cnt);
}

long long	ft_putnbr_ptr(size_t num)
{
	long long	cnt;

	cnt = 0;
	if (write(1, "0x", 2) != 2)
		return (-1);
	if (num == 0)
	{
		if (write(1, "0", 1) != 1)
			return (-1);
		return (3);
	}
	if (!print_num_base(num, 16, "0123456789abcdef", &cnt))
		return (-1);
	return (cnt + 2);
}
