/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:14:18 by jdoh              #+#    #+#             */
/*   Updated: 2022/12/02 14:32:14 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_dec(t_flag *format, t_info *info, unsigned long long num)
{
	int		idx;
	char	*result;

	if (format->order + info->print_cnt >= INT_MAX)
		return (-1);
	result = (char *) malloc(sizeof(char) * format->order);
	if (result == NULL)
		return (-1);
	idx = format->order;
	while (--idx >= 0)
	{
		result[idx] = num % 10 + '0';
		num /= 10;
	}
	if (print_nstr(info, result, format->order) < 0)
		return (free_str(result, -1));
	return (free_str(result, 0));
}

int	print_uint(t_flag *format, t_info *info, va_list *ap)
{
	unsigned long long	num;

	num = (unsigned long long) va_arg(*ap, unsigned int);
	format->empty_char = find_empty_char(format);
	format->order = find_order(num, 10);
	if (num == 0 && format->precision == 0)
		format->order = 0;
	format->print_len = ft_max(format->precision, format->order);
	if (!(format->flag & MINUS) && print_same_char(info
			, format->empty_char, format->width - format->print_len) < 0)
		return (-1);
	if (print_same_char(info, '0', format->precision - format->order) < 0
		|| print_dec(format, info, num) < 0)
		return (-1);
	if ((format->flag & MINUS) && print_same_char(info
			, format->empty_char, format->width - format->print_len) < 0)
		return (-1);
	return (0);
}

int	sign_first(t_flag *format, t_info *info, long long num)
{
	if (num < 0 || (format->flag & SPACE) || (format->flag & PLUS))
		format->print_len++;
	if (num < 0 || (format->flag & SPACE) || (format->flag & PLUS))
		if (print_same_char(info, format->sign, 1) < 0)
			return (-1);
	if (!(format->flag & MINUS) && print_same_char(info
			, format->empty_char, format->width - format->print_len) < 0)
		return (-1);
	return (0);
}

int	sign_last(t_flag *format, t_info *info, long long num)
{
	if (num < 0 || (format->flag & SPACE) || (format->flag & PLUS))
		format->print_len++;
	if (!(format->flag & MINUS) && print_same_char(info
			, format->empty_char, format->width - format->print_len) < 0)
		return (-1);
	if (num < 0 || (format->flag & SPACE) || (format->flag & PLUS))
		if (print_same_char(info, format->sign, 1) < 0)
			return (-1);
	return (0);
}

int	print_int(t_flag *format, t_info *info, va_list *ap)
{
	long long	num;

	num = (long long)va_arg(*ap, int);
	format->empty_char = find_empty_char(format);
	format->sign = find_sign(format, num);
	format->order = find_order((unsigned long long)ft_abs(num), 10);
	if (num == 0 && format->precision == 0)
		format->order = 0;
	format->print_len = ft_max(format->precision, format->order);
	if (format->empty_char == ' ' && sign_last(format, info, num) < 0)
		return (-1);
	if (format->empty_char == '0' && sign_first(format, info, num) < 0)
		return (-1);
	if (print_same_char(info, '0', format->precision - format->order) < 0
		|| print_dec(format, info, (unsigned long long)ft_abs(num)) < 0)
		return (-1);
	if ((format->flag & MINUS) && print_same_char(info
			, format->empty_char, format->width - format->print_len) < 0)
		return (-1);
	return (0);
}
