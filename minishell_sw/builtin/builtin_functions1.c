/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:36:47 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/06 14:55:16 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, UINT32_MAX);
	if (pwd == NULL)
		return (EXIT_FAILURE);
	ft_printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}

static int	export_pwd(const char *oldpwd, t_list **env_list)
{
	char		**cmds;
	const char	*pwd = getcwd(NULL, UINT32_MAX);

	if (!pwd || !oldpwd)
		return (EXIT_FAILURE);
	cmds = (char **)ft_calloc(4, sizeof(char *));
	if (!cmds)
		exit(MALLOC_FAILURE);
	cmds[0] = ft_strdup("export");
	cmds[1] = ft_strjoin("OLDPWD=", oldpwd);
	cmds[2] = ft_strjoin("PWD=", pwd);
	cmds[3] = NULL;
	if (!cmds[0] || !cmds[1] || !cmds[2])
		exit(MALLOC_FAILURE);
	return (builtin_export(cmds, env_list));
}

int	builtin_cd(char **cmds, t_list **env_list)
{
	char		*str;
	const char	*oldpwd = getcwd(NULL, UINT32_MAX);

	if (!(*(++cmds)))
	{
		ft_printf("cd: no arguments\n");
		return (EXIT_FAILURE);
	}
	if (chdir(*cmds) == -1)
	{
		str = ft_strjoin("MINI: cd: ", *cmds);
		if (!str)
			exit(MALLOC_FAILURE);
		perror(str);
		return (EXIT_FAILURE);
	}
	export_pwd(oldpwd, env_list);
	return (EXIT_SUCCESS);
}

static int	check_n(char *str)
{
	if (*str++ != '-')
		return (FALSE);
	while (*str)
		if (*str++ != 'n')
			return (FALSE);
	return (TRUE);
}

void	builtin_echo(char **strs)
{
	int		is_nl;
	int		to_check_option;

	is_nl = TRUE;
	to_check_option = TRUE;
	if (!++strs)
		ft_printf("\n");
	while (strs && *strs)
	{
		if (to_check_option)
		{
			to_check_option = check_n(*strs);
			if (to_check_option == TRUE)
			{
				is_nl = FALSE;
				++strs;
				continue ;
			}
		}
		ft_printf("%s", *strs);
		if (*++strs)
			ft_printf(" ");
	}
	if (is_nl)
		ft_printf("\n");
}
