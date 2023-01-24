/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:11:13 by jdoh              #+#    #+#             */
/*   Updated: 2022/11/30 20:47:52 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	t_info	info;
	char	buf[BUF_SIZE];
	int		print_cnt;

	info_init(&info, buf, str);
	va_start(ap, str);
	print_cnt = print_all(&info, &ap);
	va_end(ap);
	return (print_cnt);
}
