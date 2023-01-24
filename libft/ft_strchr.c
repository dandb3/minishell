/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:50:00 by jdoh              #+#    #+#             */
/*   Updated: 2022/11/10 14:47:34 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	ch;
	size_t	len;
	size_t	idx;

	ch = (char) c;
	len = ft_strlen(s);
	idx = 0;
	while (idx <= len)
	{
		if (s[idx] == ch)
			return ((char *)(s + idx));
		idx++;
	}
	return (0);
}
