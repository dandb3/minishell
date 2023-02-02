/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:17:32 by jdoh              #+#    #+#             */
/*   Updated: 2023/01/27 09:56:11 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

long long	free_ret(void *obj1, void *obj2, void *obj3, long long ret)
{
	free(obj1);
	free(obj2);
	free(obj3);
	return (ret);
}
