/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:04:28 by sunwsong          #+#    #+#             */
/*   Updated: 2023/01/29 15:06:51 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	free_ret(void *obj1, void *obj2, void *obj3, long long ret)
{
	free(obj1);
	free(obj2);
	free(obj3);
	return (ret);
}

long long	free_twoptr(char **ptr, long long ret)
{
	char	**tmp;

	if (!ptr)
		return (ret);
	tmp = ptr;
	while (*ptr)
		free(*ptr++);
	free(tmp);
	return (ret);
}
