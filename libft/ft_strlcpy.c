/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 21:28:55 by sunwsong          #+#    #+#             */
/*   Updated: 2022/11/11 20:02:37 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	idx;
	size_t	src_len;

	src_len = ft_strlen(src);
	idx = 0;
	while (idx + 1 < size && src[idx] != '\0')
	{
		dest[idx] = src[idx];
		idx++;
	}
	if (size != 0)
		dest[idx] = '\0';
	return (src_len);
}
