/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:10:36 by jdoh              #+#    #+#             */
/*   Updated: 2022/11/10 14:50:33 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	ch;
	size_t	len;
	size_t	idx;

	ch = (char) c;
	len = ft_strlen(s);
	idx = len;
	while (idx > 0)
	{
		if (s[idx] == ch)
			return ((char *)(s + idx));
		idx--;
	}
	if (s[0] == ch)
		return ((char *) s);
	return (0);
}
