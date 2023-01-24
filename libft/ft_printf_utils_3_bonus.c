/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:26:55 by jdoh              #+#    #+#             */
/*   Updated: 2022/12/02 14:55:16 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_min(int num1, int num2)
{
	if (num1 > num2)
		return (num2);
	return (num1);
}

int	ft_max(int num1, int num2)
{
	if (num1 > num2)
		return (num1);
	return (num2);
}

long long	ft_abs(long long num)
{
	if (num >= 0)
		return (num);
	return (-num);
}

int	ft_strlen_int(char *str)
{
	int	len;

	len = 0;
	while (str[len])
	{
		len++;
		if (len == INT_MAX)
			return (-1);
	}
	return (len);
}

int	free_str(char *str, int ret)
{
	free(str);
	return (ret);
}
