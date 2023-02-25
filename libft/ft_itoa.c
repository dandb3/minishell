/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:10:30 by sunwsong          #+#    #+#             */
/*   Updated: 2022/11/19 18:24:38 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*set_arr(int sign, int len, long long n)
{
	char	*str;
	int		idx;

	str = (char *)malloc(sizeof(char) * (len + sign + 1));
	if (str == 0)
		return (0);
	if (sign == 1)
		str[0] = '-';
	idx = len + sign;
	str[idx] = 0;
	while (n > 0 && idx >= sign)
	{
		str[--idx] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int			sign;
	int			len;
	long long	tmp;

	if (n == 0)
		return (ft_strdup("0"));
	len = 0;
	sign = 0;
	tmp = (long long)n;
	if (tmp < 0)
	{
		tmp *= -1;
		sign = 1;
	}
	while (tmp > 0)
	{
		len++;
		tmp /= 10;
	}
	if (n < 0)
		return (set_arr(sign, len, -(long long)n));
	return (set_arr(sign, len, (long long)n));
}
