/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:08:20 by jdoh              #+#    #+#             */
/*   Updated: 2022/11/10 15:49:08 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	move_front(char *dst, const char *src, size_t len)
{
	size_t	idx;

	idx = 0;
	while (idx < len)
	{
		dst[idx] = src[idx];
		idx++;
	}
}

static void	move_back(char *dst, const char *src, size_t len)
{
	size_t	idx;

	idx = len - 1;
	while (idx > 0)
	{
		dst[idx] = src[idx];
		idx--;
	}
	dst[0] = src[0];
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst == 0 && src == 0)
		return (0);
	if (len == 0)
		return (dst);
	if ((unsigned long long) dst < (unsigned long long) src)
		move_front((char *) dst, (const char *) src, len);
	else
		move_back((char *) dst, (const char *) src, len);
	return (dst);
}
