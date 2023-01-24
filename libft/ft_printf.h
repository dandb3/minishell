/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:11:50 by jdoh              #+#    #+#             */
/*   Updated: 2023/01/23 19:24:22 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "libft.h"

# define MINUS 1
# define PLUS 2
# define HASH 4
# define ZERO 8
# define SPACE 16
# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define BUF_SIZE 1024

typedef struct s_flag
{
	int		flag;
	int		width;
	int		precision;
	int		order;
	int		print_len;
	char	empty_char;
	char	sign;
}		t_flag;

typedef struct s_info
{
	size_t		idx;
	char		*buf;
	long long	print_cnt;
	const char	*str;
}				t_info;

int			ft_printf(const char *str, ...);

int			print_all(t_info *info, va_list *ap);

void		info_init(t_info *info, char *buf, const char *str);
void		flag_init(t_flag *flag);

int			find_order(unsigned long long num, unsigned long long base);
char		find_sign(t_flag *format, long long num);
char		find_empty_char(t_flag *format);
int			find_wildcard(t_flag *format, t_info *info, va_list *ap);

int			ft_min(int num1, int num2);
int			ft_max(int num1, int num2);
long long	ft_abs(long long num);
int			ft_strlen_int(char *str);
int			free_str(char *str, int ret);

int			print_same_char(t_info *info, char ch, int size);
int			print_nstr(t_info *info, char *str, int n);
int			ft_flush(t_info *info);

int			print_char(t_flag *format, t_info *info, va_list *ap);
int			print_str(t_flag *format, t_info *info, va_list *ap);
int			print_percent(t_flag *format, t_info *info);
int			print_addr(t_flag *format, t_info *info, va_list *ap);
int			print_xx(t_flag *format, t_info *info, va_list *ap, int upper);
int			print_uint(t_flag *format, t_info *info, va_list *ap);
int			print_int(t_flag *format, t_info *info, va_list *ap);

#endif
