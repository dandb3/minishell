/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:43:15 by sunwsong          #+#    #+#             */
/*   Updated: 2023/01/31 11:14:21 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*make_envlist(char **envp)
{
	t_list	*env_list;
	t_node	*node;
	t_env	*env;

	env_list = make_list(ENV);
	if (!env_list)
		exit(MALLOC_FAILURE);
	while (*envp)
	{
		env = make_env(*envp, TRUE);
		node = make_node(env, -1);
		if (!env || !node)
			exit(MALLOC_FAILURE);
		push_node(node, env_list);
		++envp;
	}
	sort_list(env_list);
	return (env_list);
}

char	**env_to_char(t_list *env_list)
{
		
}