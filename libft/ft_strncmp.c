/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:17:56 by jdoh              #+#    #+#             */
/*   Updated: 2022/11/10 16:16:26 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	idx;

	idx = 0;
	while (idx < n && s1[idx] == s2[idx] && s1[idx] && s2[idx])
		idx++;
	if (idx == n)
		return (0);
	return ((int)((unsigned char) s1[idx]) - (int)((unsigned char) s2[idx]));
}
