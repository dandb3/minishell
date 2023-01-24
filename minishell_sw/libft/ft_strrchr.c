/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:39:14 by sunwsong          #+#    #+#             */
/*   Updated: 2022/11/19 17:57:02 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const size_t	len = ft_strlen(s);
	size_t			idx;

	if ((char)c == 0)
		return ((char *)s + len);
	idx = len;
	while (idx-- != 0)
	{
		if (s[idx] == (char) c)
			return ((char *)s + idx);
	}
	return (0);
}
