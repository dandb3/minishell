/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:38:17 by jdoh              #+#    #+#             */
/*   Updated: 2022/11/14 20:31:13 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	be_trimmed(char ch, char const *set)
{
	size_t	idx;
	size_t	set_len;

	set_len = ft_strlen(set);
	idx = 0;
	while (idx < set_len)
	{
		if (ch == set[idx])
			return (1);
		idx++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1_len;
	size_t	start;
	size_t	end;

	if (s1 == 0 || set == 0)
		return (0);
	s1_len = ft_strlen(s1);
	if (s1_len == 0)
		return (ft_substr(s1, 5, 1));
	start = 0;
	while (start < s1_len)
	{
		if (!be_trimmed(s1[start], set))
			break ;
		start++;
	}
	end = s1_len;
	while (--end > 0)
		if (!be_trimmed(s1[end], set))
			break ;
	if (end < start)
		return (ft_substr(s1, start, 0));
	else
		return (ft_substr(s1, start, end - start + 1));
}
