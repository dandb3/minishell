/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:08:07 by sunwsong          #+#    #+#             */
/*   Updated: 2022/11/19 18:28:11 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_listdelone(t_list *lst, void (*del)(void *))
{
	if (lst == 0 || del == 0)
		return ;
	del(lst->content);
	free(lst);
}
