/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:26:23 by jdoh              #+#    #+#             */
/*   Updated: 2022/11/10 16:34:36 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	min(size_t a, size_t b)
{
	if (a > b)
		return (b);
	return (a);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const size_t	needle_len = ft_strlen(needle);
	size_t			hay_len;
	size_t			idx;
	size_t			iter;

	if (haystack == 0 && len == 0)
		return (0);
	if (needle_len == 0)
		return ((char *) haystack);
	hay_len = ft_strlen(haystack);
	len = min(len, hay_len);
	idx = -1;
	while (++idx < len)
	{
		iter = 0;
		while (iter + idx < len && iter < needle_len)
		{
			if (haystack[iter + idx] != needle[iter])
				break ;
			iter++;
		}
		if (iter == needle_len)
			return ((char *)(haystack + idx));
	}
	return (0);
}
