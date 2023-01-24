/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:03:13 by sunwsong          #+#    #+#             */
/*   Updated: 2022/11/18 19:40:43 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			idx;
	int			sign;
	long long	num;

	idx = 0;
	sign = 1;
	num = 0;
	while ((9 <= str[idx] && str[idx] <= 13) || str[idx] == ' ')
		idx++;
	if (str[idx] == '+' || str[idx] == '-')
	{
		if (str[idx++] == '-')
			sign *= -1;
	}
	while ('0' <= str[idx] && str[idx] <= '9')
		num = num * 10 + (str[idx++] - '0');
	return ((int)(num * sign));
}
