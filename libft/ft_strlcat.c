/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 13:56:58 by sunwsong          #+#    #+#             */
/*   Updated: 2022/12/14 20:09:22 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	idx;
	size_t	destlen;
	size_t	srclen;

	srclen = ft_strlen(src);
	if (size == 0)
		return (srclen);
	destlen = ft_strlen(dest);
	idx = 0;
	while (*src != '\0' && idx + destlen + 1 < size)
	{
		dest[idx + destlen] = *src++;
		idx++;
	}
	dest[idx + destlen] = '\0';
	if (size < destlen)
		return (size + srclen);
	else
		return (destlen + srclen);
}
