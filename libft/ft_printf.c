/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 20:04:46 by sunwsong          #+#    #+#             */
/*   Updated: 2022/12/27 18:05:07 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	manage_flags(va_list *ap, char ch, long long *len)
{
	long long	val;

	if (ch == 'c')
		val = ft_printf_char(va_arg(*ap, int));
	else if (ch == 's')
		val = ft_printf_string(va_arg(*ap, char *));
	else if (ch == 'p')
		val = ft_putnbr_ptr(va_arg(*ap, size_t));
	else if (ch == 'd' || ch == 'i')
		val = ft_printf_nbr(va_arg(*ap, int));
	else if (ch == 'u')
		val = ft_printf_unbr(va_arg(*ap, unsigned int));
	else if (ch == 'x' || ch == 'X')
		val = ft_printf_hex(va_arg(*ap, unsigned int), (ch == 'X'));
	else if (ch == '%')
	{
		val = write(1, "%", 1);
		if (val != 1)
			val = -1;
	}
	else
		val = -1;
	*len += val;
	return (val >= 0);
}

static long long	check_format(const char *format, va_list *ap)
{
	ssize_t		idx;
	long long	len;

	len = 0;
	idx = -1;
	while (format[++idx])
	{
		if (format[idx] == '%')
		{
			if (!manage_flags(ap, format[++idx], &len))
				return (-1);
		}
		else
		{
			if (write(1, &(format[idx]), 1) != 1)
				return (-1);
			len++;
		}
	}
	if (len > 2147483647)
		len = -1;
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	long long	len;

	if (format == NULL)
		return (-1);
	va_start(ap, format);
	len = check_format(format, &ap);
	va_end(ap);
	return (len);
}
