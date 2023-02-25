/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:31:33 by sunwsong          #+#    #+#             */
/*   Updated: 2022/11/19 17:46:44 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	idx;
	char	*str;

	if (s == 0 || ft_strlen(s) <= start)
		return (ft_strdup(""));
	if (ft_strlen(s) < start + len)
		len = ft_strlen(s) - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == 0)
		return (0);
	idx = 0;
	while (idx < len)
	{
		str[idx] = s[idx + start];
		idx++;
	}
	str[idx] = '\0';
	return (str);
}
