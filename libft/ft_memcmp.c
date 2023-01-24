/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:12:02 by jdoh              #+#    #+#             */
/*   Updated: 2022/11/10 12:26:09 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				idx;
	const unsigned char	*uc_s1;
	const unsigned char	*uc_s2;

	idx = 0;
	uc_s1 = (const unsigned char *) s1;
	uc_s2 = (const unsigned char *) s2;
	while (idx < n)
	{
		if (uc_s1[idx] != uc_s2[idx])
			return ((int) uc_s1[idx] - (int) uc_s2[idx]);
		idx++;
	}
	return (0);
}
