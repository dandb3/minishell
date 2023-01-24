/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:00:57 by jdoh              #+#    #+#             */
/*   Updated: 2022/11/10 17:24:12 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	s_len;
	size_t	idx;

	if (s == 0)
		return (0);
	s_len = ft_strlen(s);
	if (start > s_len)
		len = 0;
	else if (start + len > s_len)
		len = s_len - start;
	result = (char *) malloc(sizeof(char) * (len + 1));
	if (result == 0)
		return (0);
	idx = 0;
	while (idx < len)
	{
		result[idx] = s[start + idx];
		idx++;
	}
	result[idx] = 0;
	return (result);
}
