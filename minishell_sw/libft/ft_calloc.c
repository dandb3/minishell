/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:19:25 by sunwsong          #+#    #+#             */
/*   Updated: 2022/11/18 17:11:20 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;

	if (size && (count * size) / size != count)
		return (malloc(0));
	res = malloc(size * count);
	if (res == 0)
		return (0);
	ft_memset(res, 0, size * count);
	return (res);
}
