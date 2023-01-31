/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:50:44 by sunwsong          #+#    #+#             */
/*   Updated: 2022/11/17 18:57:16 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_listlast(t_list *lst)
{
	if (lst == 0)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
