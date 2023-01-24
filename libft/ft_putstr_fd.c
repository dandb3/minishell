/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:13:43 by jdoh              #+#    #+#             */
/*   Updated: 2022/11/11 15:53:28 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;
	size_t	idx;

	if (s == 0)
		return ;
	len = ft_strlen(s);
	idx = 0;
	while (idx < len)
	{
		ft_putchar_fd(s[idx], fd);
		idx++;
	}
}
