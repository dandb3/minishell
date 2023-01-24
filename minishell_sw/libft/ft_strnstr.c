/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:52:06 by sunwsong          #+#    #+#             */
/*   Updated: 2022/11/11 20:47:16 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t			i1;
	size_t			i2;
	const size_t	nd_len = ft_strlen(needle);

	if (haystack == 0 && len == 0)
		return (0);
	if (len > ft_strlen(haystack))
		len = ft_strlen(haystack);
	i1 = 0;
	while (i1 + nd_len < len + 1)
	{
		i2 = 0;
		while (i2 < nd_len)
		{
			if (haystack[i1 + i2] != needle[i2])
				break ;
			i2++;
		}
		if (i2 == nd_len)
			return ((char *)haystack + i1);
		i1++;
	}
	return (0);
}
