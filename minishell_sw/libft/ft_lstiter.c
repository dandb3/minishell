/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:21:58 by sunwsong          #+#    #+#             */
/*   Updated: 2022/11/18 15:19:53 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_listiter(t_list *lst, void (*f)(void *))
{
	if (lst == 0 || f == 0)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
