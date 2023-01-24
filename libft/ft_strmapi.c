/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:58:22 by jdoh              #+#    #+#             */
/*   Updated: 2022/11/11 15:04:57 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	idx;
	char	*result;

	if (s == 0 || f == 0)
		return (0);
	len = ft_strlen(s);
	result = (char *) malloc(sizeof(char) * (len + 1));
	if (result == 0)
		return (0);
	idx = 0;
	while (idx < len)
	{
		result[idx] = (*f)(idx, s[idx]);
		idx++;
	}
	result[len] = 0;
	return (result);
}
