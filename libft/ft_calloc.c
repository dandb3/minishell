/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:16:20 by jdoh              #+#    #+#             */
/*   Updated: 2022/11/10 14:41:31 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	const size_t	total_bytes = count * size;
	char			*ret_add;
	size_t			idx;

	ret_add = (char *) malloc(total_bytes);
	if (ret_add == 0)
		return (0);
	idx = 0;
	while (idx < total_bytes)
	{
		ret_add[idx] = 0;
		idx++;
	}
	return ((void *) ret_add);
}
