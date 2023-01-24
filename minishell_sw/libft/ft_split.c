/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:06:32 by sunwsong          #+#    #+#             */
/*   Updated: 2022/11/18 17:04:46 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	get_num(char const *s, char c, int *num)
{
	int	idx;

	*num = 0;
	idx = 0;
	while (s[idx])
	{
		while (s[idx] == c && s[idx])
			idx++;
		if (!s[idx])
			return ;
		(*num)++;
		while (s[idx] != c && s[idx])
			idx++;
	}
}

static char	**make_res(char const *s, char c, char **res)
{
	unsigned int	i[3];
	unsigned int	stt;

	ft_memset(i, 0, sizeof(unsigned int) * 3);
	while (s[i[0]])
	{
		while (s[i[0]] == c && s[i[0]])
			i[0]++;
		if (!s[i[0]])
			break ;
		stt = i[0];
		while (s[i[0]] != c && s[i[0]])
			i[0]++;
		res[i[1]] = ft_substr(s, stt, (i[0] - stt));
		if (res[i[1]++] == 0)
		{
			i[2] = 0;
			while (i[2] + 1 < i[1])
				free(res[i[2]++]);
			free(res);
			return (0);
		}
	}
	res[i[1]] = 0;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		num;

	if (s == 0)
		return (0);
	get_num(s, c, &num);
	if (num == 0)
	{
		res = (char **)malloc(sizeof(char *));
		if (res == 0)
			return (0);
		*res = 0;
		return (res);
	}
	res = (char **)malloc(sizeof(char *) * (num + 1));
	if (res == 0)
		return (0);
	res = make_res(s, c, res);
	return (res);
}
