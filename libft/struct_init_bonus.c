/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:15:58 by jdoh              #+#    #+#             */
/*   Updated: 2022/12/01 15:36:00 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	info_init(t_info *info, char *buf, const char *str)
{
	info->buf = buf;
	info->idx = 0;
	info->print_cnt = 0;
	info->str = str;
}

void	flag_init(t_flag *format)
{
	format->flag = 0;
	format->precision = -1;
	format->width = -1;
	format->order = 0;
	format->print_len = 0;
	format->sign = ' ';
	format->empty_char = ' ';
}
