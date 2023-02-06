/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:55:13 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/06 14:57:18 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	envlen(const char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str++ == '=')
			return (len);
		++len;
	}
	return (len);
}

int	check_valid_keyname(const char *str)
{
	size_t	idx;

	idx = 0;
	if (!str)
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
	const size_t	len = envlen(str);

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
	const int	cmp = ft_strncmp(env->key, ((t_env *)(cur->val))->key, -1);

	if (cmp == 0)
	{
		if (!(env->val))
			return (free_ret(env->key, env, NULL, SUCCESS));
		free(((t_env *)(cur->val))->val);
		((t_env *)(cur->val))->val = ft_strdup(env->val);
		if (!(((t_env *)(cur->val))->val))
			exit(EXIT_FAILURE);
		return (free_ret(env->key, env, NULL, SUCCESS));
	}
	else if (cmp < 0)
	{
		newnode = (t_node *)ft_calloc(1, sizeof(t_node));
		if (!newnode)
			exit(EXIT_FAILURE);
		newnode->val = env;
		insert_node(cur->prev, newnode);
		return (SUCCESS);
	}
	return (FAILURE);
}

int	print_envlist(t_list *list, const char *pre)
{
	t_node	*cur;

	if (list == 0)
		return (FAILURE);
	cur = list->head->next;
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
