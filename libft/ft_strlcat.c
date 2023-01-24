/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:34:28 by jdoh              #+#    #+#             */
/*   Updated: 2022/11/11 15:38:27 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	idx;
	size_t	dest_size;
	size_t	src_size;

	src_size = ft_strlen(src);
	if (dst == 0 && dstsize == 0)
		return (src_size);
	dest_size = ft_strlen(dst);
	if (dest_size >= dstsize)
		return (dstsize + src_size);
	idx = dest_size;
	while (idx + 1 < dstsize && *src)
	{
		dst[idx] = *src;
		idx++;
		src++;
	}
	dst[idx] = 0;
	return (dest_size + src_size);
}
