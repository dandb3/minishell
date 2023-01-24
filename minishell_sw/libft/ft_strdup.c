/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 19:47:34 by sunwsong          #+#    #+#             */
/*   Updated: 2022/11/19 18:06:03 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	const size_t	len = ft_strlen(src);
	size_t			idx;
	char			*str;

	idx = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == 0)
		return (0);
	while (idx < len)
	{
		str[idx] = src[idx];
		idx++;
	}
	str[idx] = '\0';
	return (str);
}
