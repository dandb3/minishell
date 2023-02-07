/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:43:15 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/07 20:59:38 by sunwsong         ###   ########.fr       */
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
	sort_envlist(env_list);
	return (env_list);
}

char	**env_to_char(t_list *env_list)
{
	char	**envp;
	size_t	idx;
	t_node	*cur;

	envp = (char **)malloc(sizeof(char *));
	if (!envp)
		exit(MALLOC_FAILURE);
	cur = env_list->head->next;
	idx = 0;
	while (cur->next)
	{
		if (((t_env *)cur->val)->val)
		{
			envp[idx] = ft_strjoin(((t_env *)cur->val)->key, "=");
			if (!envp[idx])
				exit(MALLOC_FAILURE);
			envp[idx] = ft_strjoin(envp[idx], ((t_env *)cur->val)->val);
		}
		else
			envp[idx] = ft_strdup(((t_env *)cur->val)->key);
		if (!envp[idx++])
			exit(MALLOC_FAILURE);
		cur = cur->next;
	}
	return (envp);
}

void	sort_envlist(t_list *env_list)
{
	t_node	*cur1;
	t_node	*cur2;
	t_env	*tmp;

	cur1 = env_list->head->next;
	while (cur1->next)
	{
		cur2 = cur1->next;
		while (cur2->next)
		{
			if (ft_strncmp(((t_env *)(cur1->val))->key, \
				((t_env *)(cur2->val))->key, -1) > 0)
			{
				tmp = cur1->val;
				cur1->val = cur2->val;
				cur2->val = tmp;
			}
			cur2 = cur2->next;
		}
		cur1 = cur1->next;
	}
}

char	*find_env(t_list *list, const char *to_find)
{
	t_node	*cur;

	cur = list->head->next;
	while (cur->next)
	{
		if (!ft_strcmp(((t_env *)(cur->val))->key, to_find))
			return (((t_env *)(cur->val))->val);
		cur = cur->next;
	}
	return (NULL);
}
