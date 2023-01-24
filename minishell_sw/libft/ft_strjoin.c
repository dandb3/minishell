/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:26:34 by sunwsong          #+#    #+#             */
/*   Updated: 2023/01/18 11:07:39 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	idx;
	char	*str;

	if (s1 == 0 || s2 == 0)
		return (0);
	len1 = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (len1 + ft_strlen(s2) + 1));
	if (str == 0)
		return (0);
	idx = 0;
	while (s1[idx])
	{
		str[idx] = s1[idx];
		idx++;
	}
	idx = 0;
	while (s2[idx])
	{
		str[len1 + idx] = s2[idx];
		idx++;
	}
	str[len1 + idx] = '\0';
	return (str);
}
