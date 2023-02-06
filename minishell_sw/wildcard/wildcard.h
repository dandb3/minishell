/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:53:27 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/06 21:00:50 by sunwsong         ###   ########.fr       */
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

#endif