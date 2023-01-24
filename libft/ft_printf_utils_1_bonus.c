/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 19:21:51 by jdoh              #+#    #+#             */
/*   Updated: 2022/12/02 14:55:17 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_same_char(t_info *info, char ch, int size)
{
	int	idx;

	idx = -1;
	while (++idx < size)
	{
		info->buf[info->idx++] = ch;
		if (info->idx == BUF_SIZE && ft_flush(info) < 0)
			return (-1);
		info->print_cnt++;
		if (info->print_cnt >= INT_MAX)
			return (-1);
	}
	return (0);
}

int	print_nstr(t_info *info, char *str, int n)
{
	int	idx;

	idx = 0;
	while (idx < n && str[idx])
		if (print_same_char(info, str[idx++], 1) < 0)
			return (-1);
	return (0);
}

int	ft_flush(t_info *info)
{
	int	ret;

	ret = write(1, info->buf, info->idx);
	info->idx = 0;
	return (ret);
}
