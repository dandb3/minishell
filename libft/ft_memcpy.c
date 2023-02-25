/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:06:31 by sunwsong          #+#    #+#             */
/*   Updated: 2022/12/14 20:10:09 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*s;
	size_t			idx;

	s = (unsigned char *)src;
	if (dst == 0 && src == 0)
		return (0);
	idx = 0;
	while (idx < n)
	{
		((unsigned char *)dst)[idx] = *s++;
		idx++;
	}
	return (dst);
}
