/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:33:55 by jdoh              #+#    #+#             */
/*   Updated: 2022/11/11 15:06:27 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*make_zero(void)
{
	char	*result;

	result = (char *) malloc(sizeof(char) * 2);
	if (result == 0)
		return (0);
	result[0] = '0';
	result[1] = 0;
	return (result);
}

static int	count_order(int n)
{
	int	order;

	order = 0;
	if (n < 0)
		order++;
	while (n != 0)
	{
		order++;
		n /= 10;
	}
	return (order);
}

char	*ft_itoa(int n)
{
	long long	ll_n;
	int			order;
	char		*result;
	int			idx;

	if (n == 0)
		return (make_zero());
	order = count_order(n);
	result = (char *) malloc(sizeof(char) * (order + 1));
	if (result == 0)
		return (0);
	result[order] = 0;
	idx = order - 1;
	ll_n = (long long) n;
	if (ll_n < 0)
		ll_n = -ll_n;
	while (ll_n != 0)
	{
		result[idx--] = ll_n % 10 + '0';
		ll_n /= 10;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}
