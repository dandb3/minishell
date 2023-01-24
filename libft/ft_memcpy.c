/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:01:05 by jdoh              #+#    #+#             */
/*   Updated: 2022/11/10 15:04:22 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*c_dst;
	const char	*c_src;
	size_t		idx;

	if (dst == 0 && src == 0)
		return (0);
	idx = 0;
	c_dst = (char *) dst;
	c_src = (const char *) src;
	while (idx < n)
	{
		c_dst[idx] = c_src[idx];
		idx++;
	}
	return (dst);
}
