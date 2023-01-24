/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:39:14 by sunwsong          #+#    #+#             */
/*   Updated: 2022/11/11 20:02:30 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const size_t	len = ft_strlen(s);
	size_t			idx;

	idx = 0;
	if ((char)c == 0)
		return ((char *)s + len);
	while (idx < len)
	{
		if (s[idx] == (char) c)
			return ((char *)s + idx);
		idx++;
	}
	return (0);
}
