/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:05:48 by jdoh              #+#    #+#             */
/*   Updated: 2022/11/11 15:09:34 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	len;
	size_t	idx;

	if (s == 0 || f == 0)
		return ;
	len = ft_strlen(s);
	idx = 0;
	while (idx < len)
	{
		(*f)(idx, s + idx);
		idx++;
	}
}
