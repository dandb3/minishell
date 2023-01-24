/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:21:51 by jdoh              #+#    #+#             */
/*   Updated: 2022/11/10 17:27:20 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;
	size_t	idx;

	if (s1 == 0 || s2 == 0)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = (char *) malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (result == 0)
		return (0);
	idx = 0;
	while (idx < s1_len)
	{
		result[idx] = s1[idx];
		idx++;
	}
	while (idx < s1_len + s2_len)
	{
		result[idx] = s2[idx - s1_len];
		idx++;
	}
	result[idx] = 0;
	return (result);
}
