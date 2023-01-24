/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:52:29 by sunwsong          #+#    #+#             */
/*   Updated: 2022/11/17 21:01:14 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	loc[2];

	if (s1 == 0)
		return (0);
	if (ft_memcmp("", s1, 1) == 0)
		return (ft_strdup(""));
	loc[0] = 0;
	while (s1[loc[0]])
	{
		if (ft_strchr(set, s1[loc[0]]) == 0)
			break ;
		loc[0]++;
	}
	loc[1] = ft_strlen(s1) - 1;
	while (s1[loc[1]] && loc[0] < loc[1])
	{
		if (ft_strchr(set, s1[loc[1]]) == 0)
			break ;
		loc[1]--;
	}
	return (ft_substr(s1, loc[0], loc[1] - loc[0] + 1));
}
