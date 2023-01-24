/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:27:02 by jdoh              #+#    #+#             */
/*   Updated: 2022/12/01 21:09:33 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(t_flag *format, t_info *info, va_list *ap)
{
	char	ch;

	ch = va_arg(*ap, int);
	if (!(format->flag & MINUS)
		&& print_same_char(info, ' ', format->width - 1) < 0)
		return (-1);
	if (print_same_char(info, ch, 1) < 0)
		return (-1);
	if ((format->flag & MINUS)
		&& print_same_char(info, ' ', format->width - 1) < 0)
		return (-1);
	return (0);
}

int	print_str(t_flag *format, t_info *info, va_list *ap)
{
	char	*str;
	int		print_len;

	str = va_arg(*ap, char *);
	if (str == NULL)
		str = "(null)";
	print_len = ft_strlen_int(str);
	if (print_len == -1 || print_len + info->print_cnt >= INT_MAX)
		return (-1);
	if (format->precision != -1)
		print_len = ft_min(print_len, format->precision);
	if (!(format->flag & MINUS)
		&& print_same_char(info, ' ', format->width - print_len) < 0)
		return (-1);
	if (print_nstr(info, str, print_len) < 0)
		return (-1);
	if ((format->flag & MINUS)
		&& print_same_char(info, ' ', format->width - print_len) < 0)
		return (-1);
	return (0);
}

int	print_percent(t_flag *format, t_info *info)
{
	char	empty_char;

	empty_char = find_empty_char(format);
	if (!(format->flag & MINUS)
		&& print_same_char(info, empty_char, format->width - 1) < 0)
		return (-1);
	if (print_same_char(info, '%', 1) < 0)
		return (-1);
	if ((format->flag & MINUS)
		&& print_same_char(info, empty_char, format->width - 1) < 0)
		return (-1);
	return (0);
}
