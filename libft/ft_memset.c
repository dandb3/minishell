/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:34:28 by jdoh              #+#    #+#             */
/*   Updated: 2022/11/07 16:54:46 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			idx;
	unsigned char	*pp;

	idx = 0;
	pp = (unsigned char *) b;
	while (idx < len)
	{
		pp[idx] = (unsigned char) c;
		idx++;
	}
	return (b);
}
