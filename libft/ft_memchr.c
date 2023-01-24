/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:43:29 by jdoh              #+#    #+#             */
/*   Updated: 2022/11/10 14:50:51 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				idx;
	const unsigned char	*pp;

	idx = 0;
	pp = (const unsigned char *) s;
	while (idx < n)
	{
		if (pp[idx] == (unsigned char) c)
			return ((void *)(pp + idx));
		idx++;
	}
	return (0);
}	
