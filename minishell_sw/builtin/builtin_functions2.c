/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:20:12 by sunwsong          #+#    #+#             */
/*   Updated: 2023/01/30 13:42:30 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static long long	builtin_atoi(const char *str)
{
	int			idx;
	int			sign;
	long long	num;

	idx = 0;
	sign = 1;
	num = 0;
	while ((9 <= str[idx] && str[idx] <= 13) || str[idx] == ' ')
		idx++;
	if (str[idx] == '+' || str[idx] == '-')
		if (str[idx++] == '-')
			sign *= -1;
	while ('0' <= str[idx] && str[idx] <= '9')
		num = num * 10 + (str[idx++] - '0');
	if (str[idx] != 0 && (str[idx] < '0' || '9' < str[idx]))
	{
		ft_printf("MINI: exit: %s: numeric argument required\n", str);
		exit(255);
	}
	return (num * sign);
}

void	builtin_exit(char **cmds)
{
	long long	ret;
	size_t		len;

	if (!(*(++cmds)))
		exit(EXIT_SUCCESS);
	ret = builtin_atoi(*cmds);
	len = ft_strlen(*cmds);
	if (len >= 21)
	{
		ft_printf("MINI: exit: %s: numeric argument required\n", *cmds);
		exit(255);
	}
	if (len >= 1)
	{
		if ((*cmds)[len - 1] - '0' != ret % 10)
		{
			ft_printf("MINI: exit: %s: numeric argument required\n", *cmds);
			exit(255);
		}
	}
	exit((unsigned char)ret);
}

int	builtin_export(char **cmds, t_list **env_list)
{
	t_node	*cur;
	t_env	*env;

	if (!*(++cmds))
		return (print_envlist(*env_list, "declare -x "));
	while (*cmds)
	{
		cur = (*env_list)->head->next;
		env = make_env(*cmds++, TRUE);
		if (!env)
			return (FAILURE);
		while (cur)
		{
			if (push_environ(env, cur) == SUCCESS)
				break ;
			cur = cur->next;
		}
	}
	return (SUCCESS);
}

void	builtin_env(t_list **env_list)
{
	print_envlist(*env_list, NULL);
}

void	builtin_unset(char **cmds, t_list **env_list)
{
	t_node	*cur;
	size_t	len;

	while (*(++cmds))
	{
		cur = (*env_list)->head->next;
		while (cur->next)
		{
			len = envlen(*cmds);
			if (!ft_strncmp(*cmds, ((t_env *)cur->val)->key, len))
			{
				del_node(cur, ENV);
				break ;
			}
			cur = cur->next;
		}
	}
	return ;
}
