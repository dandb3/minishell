/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:55:13 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/18 13:17:03 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	get_envlen(const char *str)
{
	size_t	idx;

	idx = -1;
	if (*str == '?')
		return (1);
	while (str[++idx])
	{
		if (((!ft_isalnum(str[idx]) && idx != 0) || \
			(!ft_isalpha(str[idx]) && idx == 0)) && \
			str[idx] != '_')
			return (idx);
	}
	return (idx);
}

int	check_valid_keyname(const char *str)
{
	size_t	idx;

	idx = 0;
	if (!str)
		return (FAILURE);
	if (*str == '=')
		return (FAILURE);
	while (str[idx] && str[idx] != '=')
	{
		if (((!ft_isalnum(str[idx]) && idx != 0) || \
			(!ft_isalpha(str[idx]) && idx == 0)) && \
			str[idx] != '_')
			return (FALSE);
		++idx;
	}
	return (TRUE);
}

t_env	*make_env(const char *str, int to_check)
{
	t_env			*newenv;
	const size_t	len = get_envlen(str);

	if (to_check && !check_valid_keyname(str))
	{
		ft_printf("MINI: export: \'%s\': not a valid identifier\n", str);
		return (NULL);
	}
	newenv = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!newenv)
		exit(MALLOC_FAILURE);
	newenv->key = ft_substr(str, 0, len);
	if (!newenv->key)
		exit(MALLOC_FAILURE);
	if (len < ft_strlen(str))
	{
		newenv->val = ft_substr(str, len + 1, ft_strlen(str) - len);
		if (!newenv->val)
			exit(MALLOC_FAILURE);
	}
	return (newenv);
}

int	push_environ(t_env *env, t_node *cur)
{
	t_node		*newnode;
	const int	cmp = ft_strcmp(env->key, ((t_env *)(cur->val))->key);

	if (cmp == 0)
	{
		if (env->val == NULL)
			return (free_ret(env->key, env, NULL, SUCCESS));
		free(((t_env *)(cur->val))->val);
		((t_env *)(cur->val))->val = ft_strdup(env->val);
		if (((t_env *)(cur->val))->val == NULL)
			exit(MALLOC_FAILURE);
		return (free_ret(env->val, env->key, env, SUCCESS));
	}
	else if (cmp < 0)
	{
		newnode = (t_node *)ft_calloc(1, sizeof(t_node));
		if (!newnode)
			exit(MALLOC_FAILURE);
		newnode->val = env;
		insert_node(cur->prev, newnode);
		printf("insert node fin\n");
		return (SUCCESS);
	}
	return (FAILURE);
}

int	print_envlist(const char *pre)
{
	t_node	*cur;

	if (g_env_list == 0)
		return (FAILURE);
	cur = g_env_list->head->next->next;
	while (cur->next)
	{
		if (cur->next == NULL)
			break ;
		if (pre)
			ft_printf("%s", pre);
		if (!pre && !(((t_env *)(cur->val))->val))
		{
			cur = cur->next;
			continue ;
		}
		ft_printf("%s", (((t_env *)(cur->val))->key));
		if (((t_env *)(cur->val))->val)
			ft_printf("=\"%s\"", (((t_env *)(cur->val))->val));
		ft_printf("\n");
		cur = cur->next;
	}
	return (SUCCESS);
}
