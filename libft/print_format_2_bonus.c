/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 20:27:23 by jdoh              #+#    #+#             */
/*   Updated: 2022/12/02 14:22:06 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex(t_flag *format, t_info *info
			, unsigned long long num, int upper)
{
	int		idx;
	char	*hex;
	char	*result;

	if (!upper)
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	if (format->order + info->print_cnt >= INT_MAX)
		return (-1);
	result = (char *) malloc(sizeof(char) * format->order);
	if (result == NULL)
		return (-1);
	idx = format->order;
	while (--idx >= 0)
	{
		result[idx] = hex[num % 16];
		num /= 16;
	}
	if (print_nstr(info, result, format->order) < 0)
		return (free_str(result, -1));
	return (free_str(result, 0));
}

int	print_addr(t_flag *format, t_info *info, va_list *ap)
{
	unsigned long long	addr;

	addr = (unsigned long long) va_arg(*ap, void *);
	format->order = find_order(addr, 16);
	format->print_len = format->order + 2;
	if (!(format->flag & MINUS)
		&& print_same_char(info, ' ', format->width - format->print_len) < 0)
		return (-1);
	if (print_nstr(info, "0x", 2) < 0 || print_hex(format, info, addr, 0) < 0)
		return (-1);
	if ((format->flag & MINUS)
		&& print_same_char(info, ' ', format->width - format->print_len) < 0)
		return (-1);
	return (0);
}

int	pre_last(t_flag *format, t_info *info, char *prefix
			, unsigned long long num)
{
	if (!(format->flag & MINUS) && print_same_char(info
			, format->empty_char, format->width - format->print_len) < 0)
		return (-1);
	if (num && (format->flag & HASH) && print_nstr(info, prefix, 2) < 0)
		return (-1);
	return (0);
}

int	pre_first(t_flag *format, t_info *info, char *prefix
			, unsigned long long num)
{
	if (num && (format->flag & HASH) && print_nstr(info, prefix, 2) < 0)
		return (-1);
	if (!(format->flag & MINUS) && print_same_char(info
			, format->empty_char, format->width - format->print_len) < 0)
		return (-1);
	return (0);
}

int	print_xx(t_flag *format, t_info *info, va_list *ap, int upper)
{
	unsigned long long	num;
	char				*prefix;

	prefix = "0x";
	if (upper)
		prefix = "0X";
	num = (unsigned long long) va_arg(*ap, unsigned int);
	format->order = find_order(num, 16);
	if (num == 0 && format->precision == 0)
		format->order = 0;
	format->print_len = ft_max(format->precision, format->order);
	format->empty_char = find_empty_char(format);
	if ((format->flag & HASH) && num)
		format->print_len += 2;
	if (format->empty_char == ' ' && pre_last(format, info, prefix, num) < 0)
		return (-1);
	if (format->empty_char == '0' && pre_first(format, info, prefix, num) < 0)
		return (-1);
	if (print_same_char(info, '0', format->precision - format->order) < 0
		|| print_hex(format, info, num, upper) < 0)
		return (-1);
	if ((format->flag & MINUS) && print_same_char(info
			, format->empty_char, format->width - format->print_len) < 0)
		return (-1);
	return (0);
}
