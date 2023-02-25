/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:28:23 by sunwsong          #+#    #+#             */
/*   Updated: 2022/11/11 20:02:40 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		res;
	size_t	idx;

	res = 0;
	idx = 0;
	while (s1[idx] != '\0' && s2[idx] != '\0' && res == 0 && idx < n)
	{
		res = (int)((unsigned char)s1[idx] - (unsigned char)s2[idx]);
		idx++;
	}
	if (res == 0 && idx < n)
		res = (int)((unsigned char)s1[idx] - (unsigned char)s2[idx]);
	return (res);
}
