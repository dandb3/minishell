/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:28:30 by sunwsong          #+#    #+#             */
/*   Updated: 2022/11/15 17:13:25 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			idx;
	unsigned char	*ptr;

	idx = 0;
	ptr = (unsigned char *)b;
	while (idx < len)
	{
		*ptr++ = (unsigned char)c;
		idx++;
	}
	return (b);
}
