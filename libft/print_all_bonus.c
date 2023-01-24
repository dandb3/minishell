/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:21:27 by jdoh              #+#    #+#             */
/*   Updated: 2022/12/02 16:57:30 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_format(t_flag *format, t_info *info, va_list *ap)
{
	int	status;

	status = 0;
	if (*(info->str) == 'c')
		status = print_char(format, info, ap);
	else if (*(info->str) == 's')
		status = print_str(format, info, ap);
	else if (*(info->str) == 'p')
		status = print_addr(format, info, ap);
	else if (*(info->str) == 'd' || *(info->str) == 'i')
		status = print_int(format, info, ap);
	else if (*(info->str) == 'u')
		status = print_uint(format, info, ap);
	else if (*(info->str) == 'x')
		status = print_xx(format, info, ap, 0);
	else if (*(info->str) == 'X')
		status = print_xx(format, info, ap, 1);
	else if (*(info->str) == '%')
		status = print_percent(format, info);
	(info->str)++;
	return (status);
}

int	my_atoi(t_info *info, int *val)
{
	long long	result;

	result = 0;
	while (ft_isdigit(*(info->str)))
	{
		result = 10 * result + *((info->str)++) - '0';
		if (result >= INT_MAX)
			return (-1);
	}
	if (result + info->print_cnt >= INT_MAX)
		return (-1);
	*val = (int) result;
	return (0);
}

void	check_flag(t_flag *format, t_info *info)
{
	if (*(info->str) == '-')
		format->flag |= MINUS;
	else if (*(info->str) == '+')
		format->flag |= PLUS;
	else if (*(info->str) == '#')
		format->flag |= HASH;
	else if (*(info->str) == '0')
		format->flag |= ZERO;
	else if (*(info->str) == ' ')
		format->flag |= SPACE;
	(info->str)++;
}

int	f_string(t_info *info, va_list *ap)
{
	t_flag	format;

	flag_init(&format);
	while (ft_strchr("+ 0-#", *(info->str)))
		check_flag(&format, info);
	if (ft_isdigit(*(info->str)) && my_atoi(info, &(format.width)) == -1)
		return (-1);
	else if (*(info->str) == '*')
		if (find_wildcard(&format, info, ap) < 0)
			return (-1);
	if (*(info->str) == '.')
	{
		(info->str)++;
		if (my_atoi(info, &(format.precision)) == -1)
			return (-1);
	}
	if (ft_strchr("cspdiuxX%", *(info->str)))
		if (print_format(&format, info, ap) == -1)
			return (-1);
	return (0);
}

int	print_all(t_info *info, va_list *ap)
{
	while (*(info->str))
	{
		if (*(info->str) == '%')
		{
			(info->str)++;
			if (f_string(info, ap) == -1)
				return (-1);
		}
		else
		{
			info->buf[(info->idx)++] = *((info->str)++);
			(info->print_cnt)++;
		}
		if (info->print_cnt == INT_MAX)
			return (-1);
		if (info->idx >= BUF_SIZE)
		{
			if (write(1, info->buf, BUF_SIZE) < 0)
				return (-1);
			info->idx = 0;
		}
	}
	if (write(1, info->buf, info->idx) < 0)
		return (-1);
	return ((int)info->print_cnt);
}
