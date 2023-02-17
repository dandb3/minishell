/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:53:27 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/17 15:57:55 by sunwsong         ###   ########.fr       */
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
char	*wilddup(char *str, size_t len);
char	disc(t_wild *wild, char **dp, size_t widx, size_t nidx);

#endif