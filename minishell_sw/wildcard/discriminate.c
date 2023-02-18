/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   discriminate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:46:00 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/18 19:14:36 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

// static char	set_val(char *ptr, char val)
// {
// 	*ptr = val;
// 	return (val);
// }

void	print_all(t_wild *wild, size_t widx, size_t nidx) // 지우세용
{
	printf("wild->wstr: %s\n", wild->wstr);
	printf("wild->name: %s\n", wild->name);
	printf("wild->wlen: %zu\n", wild->wlen);
	printf("wild->nlen: %zu\n", wild->nlen);
	printf("widx: %zu\n", widx);
	printf("nidx: %zu\n", nidx);
}

char	disc(t_wild *wild, char **dp, size_t widx, size_t nidx)
{
	if (widx < wild->wlen && nidx < wild->nlen \
		&& dp[widx][nidx] != -1)
		return (dp[widx][nidx]);
	if (widx < wild->wlen && nidx < wild->nlen \
		&& wild->wstr[widx] == wild->name[nidx])
		return (dp[widx][nidx] = disc(wild, dp, widx + 1, nidx + 1));
	if (widx == wild->wlen)
	{
		if (nidx == wild->nlen)
			return (1);
		return (0);
	}
	if (wild->wstr[widx] == '\0' && widx != wild->wlen)
		if (disc(wild, dp, widx + 1, nidx)
			|| (nidx < wild->nlen && disc(wild, dp, widx, nidx + 1)))
			return (dp[widx][nidx] = 1);
	return (dp[widx][nidx] = 0);
}

/*
char	disc(t_wild *wild, char **dp, size_t widx, size_t nidx)
{
	if (widx < wild->wlen && nidx < wild->nlen \
		&& dp[widx][nidx] != -1)
		return (dp[widx][nidx]);
	if (widx < wild->wlen && nidx < wild->nlen \
		&& wild->wstr[widx] == wild->name[nidx])
		return (set_val(&dp[widx][nidx], \
			disc(wild, dp, widx + 1, nidx + 1)));
	if (widx == wild->wlen)
	{
		if (nidx == wild->nlen)
			return (1);
		return (0);
	}
	if (wild->wstr[widx] == '\0' && widx != wild->wlen)
		if (disc(wild, dp, widx + 1, nidx)
			|| (nidx < wild->nlen && disc(wild, dp, widx, nidx + 1)))
			return (set_val(&dp[widx][nidx], 1));
	return (set_val(&dp[widx][nidx], 0));
}
*/