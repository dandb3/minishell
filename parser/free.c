/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:17:32 by jdoh              #+#    #+#             */
/*   Updated: 2023/01/24 11:26:59 by jdoh             ###   ########seoul.kr  */
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
