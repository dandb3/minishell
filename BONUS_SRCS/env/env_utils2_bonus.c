/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:43:15 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/25 13:03:43 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

t_list	*make_envlist(char **envp)
{
	t_list	*env_list;
	t_node	*node;
	t_env	*env;

	env_list = make_list(ENV);
	env = make_env("?", FALSE);
	env->val = ft_strdup("0");
	if (env->val == NULL)
		exit(MALLOC_FAILURE);
	node = make_node(env, -1);
	push_node(node, env_list);
	--(env_list->size);
	while (*envp)
	{
		env = make_env(*envp++, TRUE);
		if (!env || !node)
			exit(MALLOC_FAILURE);
		node = make_node(env, -1);
		push_node(node, env_list);
	}
	sort_envlist(env_list);
	return (env_list);
}

char	**env_to_char(void)
{
	char	**envp;
	size_t	idx;
	t_node	*cur;

	envp = (char **)ft_calloc(g_env_list->size + 1, sizeof(char *));
	if (!envp)
		exit(MALLOC_FAILURE);
	cur = g_env_list->head->next->next;
	idx = 0;
	while (cur->next)
	{
		if (((t_env *)cur->val)->val)
		{
			envp[idx] = ft_strjoin(((t_env *)cur->val)->key, "=");
			if (!envp[idx])
				exit(MALLOC_FAILURE);
			envp[idx] = strjoin_and_free(envp[idx], ((t_env *)cur->val)->val);
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

	cur1 = env_list->head->next->next;
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

char	*find_env_val(char const *key)
{
	t_node	*cur_env;
	char	*ret;

	if (key == NULL)
		return (NULL);
	cur_env = g_env_list->head->next;
	while (cur_env->next != NULL)
	{
		if (!ft_strcmp(((t_env *)(cur_env->val))->key, key))
		{
			ret = ft_strdup(((t_env *)(cur_env->val))->val);
			if (ret == NULL)
				exit(MALLOC_FAILURE);
			return (ret);
		}
		cur_env = cur_env->next;
	}
	return (NULL);
}

long long	set_exitcode(int exit_code, long long ret)
{
	char	*code;

	code = ft_itoa(exit_code);
	if (!code)
		exit(MALLOC_FAILURE);
	free(((t_env *)g_env_list->head->next->val)->val);
	((t_env *)g_env_list->head->next->val)->val = code;
	return (ret);
}
