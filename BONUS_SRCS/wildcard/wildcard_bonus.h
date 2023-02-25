/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:53:27 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/25 13:03:43 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_BONUS_H
# define WILDCARD_BONUS_H

# include <dirent.h>
# include "../minishell_bonus.h"

typedef struct s_wild{
	char	*wstr;
	char	*name;
	size_t	wlen;
	size_t	nlen;
}	t_wild;

void	free_and_realloc_dp(t_wild *wild, char **dp);
void	push_wstr(t_list *res, char *wstr, size_t wlen);
char	disc(t_wild *wild, char **dp, size_t widx, size_t nidx);

#endif