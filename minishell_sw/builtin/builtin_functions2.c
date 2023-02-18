/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:20:12 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/18 19:44:52 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static long long	builtin_atoi(const char *str)
{
	size_t		idx;
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
	if ((str[idx] != 0 && (str[idx] < '0' || '9' < str[idx])) || idx >= 21)
	{
		ft_printf("exit\nMINI: exit: %s: numeric argument required\n", str);
		exit(255);
	}
	return (num * sign);
}

void	builtin_exit(char **cmds)
{
	long long	ret;
	size_t		len;

	if (!(*(++cmds)))
	{
		ft_printf("exit\n");
		exit(get_exitcode());
	}
	ret = builtin_atoi(*cmds);
	len = ft_strlen(*cmds);
	if (len >= 19)
	{
		if ((*cmds)[len - 1] - '0' != (ret % 10) * ((ret > 0) * 2 - 1))
		{
			ft_printf("exit\nMINI: exit: %s: numeric argument required\n", *cmds);
			exit(255);
		}
	}
	ft_printf("exit\n");
	exit((unsigned char)ret);
}

int	builtin_export(char **cmds)
{
	t_node	*cur;
	t_env	*env;
	int		exit_code;

	exit_code = 0;
	if (!*(++cmds))
		return (print_envlist("declare -x "));
	while (*cmds)
	{
		cur = g_env_list->head->next->next;
		env = make_env(*cmds++, TRUE);
		if (!env)
		{
			exit_code = 1;
			continue ;
		}
		while (cur)
		{
			if (push_environ(env, cur) == SUCCESS)
				break ;
			cur = cur->next;
		}
	}
	return (exit_code);
}

int	builtin_env(char **cmds)
{
	if (cmds[1] != NULL)
	{
		ft_printf("env: env does not need arguments\n");
		return (EXIT_FAILURE);
	}
	print_envlist(NULL);
	return (EXIT_SUCCESS);
}

int	builtin_unset(char **cmds)
{
	t_node	*cur;
	int		exit_code;

	exit_code = 0;
	while (*(++cmds))
	{
		if (check_valid_keyname(*cmds) == FALSE)
		{
			ft_printf("MINI: unset: '%s': not a valid identifier\n", *cmds);
			exit_code = 1;
			continue ;
		}
		cur = g_env_list->head->next->next;
		while (cur->next)
		{
			if (!ft_strncmp(*cmds, ((t_env *)cur->val)->key, get_envlen(*cmds)))
			{
				del_node(cur, ENV);
				--(g_env_list->size);
				break ;
			}
			cur = cur->next;
		}
	}
	return (exit_code);
}
