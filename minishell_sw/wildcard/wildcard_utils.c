/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 21:08:49 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/17 18:03:28 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	free_and_realloc_dp(t_wild *wild, char **dp)
{
	size_t	idx;

	idx = -1;
	while (++idx < wild->wlen)
	{
		free(dp[idx]);
		dp[idx] = NULL;
	}
	idx = -1;
	while (++idx < wild->wlen)
	{
		dp[idx] = (char *)malloc(sizeof(char) * wild->nlen);
		if (!dp[idx])
			exit(MALLOC_FAILURE);
		ft_memset(dp[idx], -1, sizeof(char) * wild->nlen);
	}
}

char	*wilddup(char *str, size_t len)
{
	size_t	idx;
	char	*res;

	res = (char *)ft_calloc(len + 1, sizeof(char));
	if (!res)
		exit(MALLOC_FAILURE);
	idx = -1;
	while (++idx < len)
		res[idx] = str[idx];
	return (res);
}
