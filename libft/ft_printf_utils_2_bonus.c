/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:49:19 by jdoh              #+#    #+#             */
/*   Updated: 2022/12/01 21:00:47 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	find_order(unsigned long long num, unsigned long long base)
{
	int	order;

	order = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num /= base;
		order++;
	}
	return (order);
}

char	find_sign(t_flag *format, long long num)
{
	char	sign;

	sign = '-';
	if (format->flag & PLUS)
	{
		if (num >= 0)
			sign = '+';
	}
	else if (format->flag & SPACE)
	{
		if (num >= 0)
			sign = ' ';
	}
	return (sign);
}

char	find_empty_char(t_flag *format)
{
	char	empty_char;

	empty_char = ' ';
	if (!(format->flag & MINUS) && (format->flag & ZERO)
		&& (format->precision < 0))
		empty_char = '0';
	return (empty_char);
}

int	find_wildcard(t_flag *format, t_info *info, va_list *ap)
{
	format->width = va_arg(*ap, int);
	if (format->width == INT_MIN)
		return (-1);
	if (format->width < 0)
	{
		format->flag |= MINUS;
		format->width = -format->width;
	}
	(info->str)++;
	return (0);
}
