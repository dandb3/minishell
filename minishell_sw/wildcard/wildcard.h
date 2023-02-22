/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:53:27 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/21 20:39:59 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include <dirent.h>
# include "../minishell.h"

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