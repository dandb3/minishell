/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 21:08:49 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/21 20:39:36 by sunwsong         ###   ########.fr       */
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

void	push_wstr(t_list *res, char *wstr, size_t wlen)
{
	char	*new_wstr;
	size_t	idx;

	idx = -1;
	while (++idx < wlen)
		if (wstr[idx] == 0)
			wstr[idx] = '*';
	new_wstr = ft_strdup(wstr);
	if (new_wstr == NULL)
		exit(MALLOC_FAILURE);
	push_node(make_node(new_wstr, -1), res);
}
