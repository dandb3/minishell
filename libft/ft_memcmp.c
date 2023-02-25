/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:40:53 by sunwsong          #+#    #+#             */
/*   Updated: 2022/11/18 19:21:37 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int		dif;
	size_t	idx;

	idx = 0;
	if (n == 0)
		return (0);
	while (idx < n - 1)
	{
		dif = ((unsigned char *)s1)[idx] - ((unsigned char *)s2)[idx];
		if (dif != 0)
			return (dif);
		idx++;
	}
	return (((unsigned char *)s1)[idx] - ((unsigned char *)s2)[idx]);
}
