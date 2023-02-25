/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:47:39 by sunwsong          #+#    #+#             */
/*   Updated: 2022/11/19 18:12:32 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			idx;
	unsigned char	*d;
	unsigned char	*s;

	if (dst == 0 && src == 0)
		return (0);
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	idx = 0;
	if (dst < src)
	{
		while (++idx <= len)
			d[idx - 1] = s[idx - 1];
	}
	else
	{
		while (++idx <= len)
			d[len - idx] = s[len - idx];
	}
	return (dst);
}
