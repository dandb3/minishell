/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:25:31 by jdoh              #+#    #+#             */
/*   Updated: 2022/11/10 17:24:35 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*result;
	size_t	len;
	size_t	idx;

	len = ft_strlen(s1);
	result = (char *) malloc(sizeof(char) * (len + 1));
	if (result == 0)
		return (0);
	idx = 0;
	while (idx <= len)
	{
		result[idx] = s1[idx];
		idx++;
	}
	return (result);
}
