/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:51:26 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/14 17:39:21 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short	get_exitcode(void)
{
	t_node	*cur;
	int		exit_code;

	cur = g_env_list->head->next;
	exit_code = (short)ft_atoi(((t_env *)cur->val)->val);
	return (exit_code);
}
