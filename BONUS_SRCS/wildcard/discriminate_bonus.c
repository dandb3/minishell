/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   discriminate_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:46:00 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/25 13:03:43 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard_bonus.h"

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
