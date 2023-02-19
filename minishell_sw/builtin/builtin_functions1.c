/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:36:47 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/19 13:12:24 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, UINT32_MAX);
	if (pwd == NULL)
		exit(MALLOC_FAILURE);
	ft_printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}

static int	export_pwd(char *nxtpwd, char *oldpwd)
{
	char	**cmds;
	char	*pwd;

	pwd = getcwd(NULL, UINT32_MAX);
	cmds = (char **)ft_calloc(4, sizeof(char *));
	if (!cmds || !pwd)
		exit(MALLOC_FAILURE);
	cmds[0] = ft_strdup("export");
	cmds[1] = ft_strjoin("OLDPWD=", oldpwd);
	cmds[2] = ft_strjoin("PWD=", pwd);
	cmds[3] = NULL;
	if (!cmds[0] || !cmds[1] || !cmds[2])
		exit(MALLOC_FAILURE);
	builtin_export(cmds);
	free_ret(cmds[0], cmds[1], cmds[2], 0);
	free(nxtpwd);
	return (free_ret(cmds, oldpwd, pwd, 0));
}

int	builtin_cd(char **cmds)
{
	char		*oldpwd;
	char		*nxtpwd;

	nxtpwd = NULL;
	if (!(*(++cmds)))
	{
		nxtpwd = find_env_val("HOME");
		if (!nxtpwd)
			return ((write(STDERR_FILENO, HOME_NOT_SET, 23) & 0) | 1);
	}
	if (!nxtpwd)
		nxtpwd = ft_strdup(*cmds);
	oldpwd = getcwd(NULL, UINT32_MAX);
	if (!nxtpwd || !oldpwd)
		exit(MALLOC_FAILURE);
	if (ft_strlen(nxtpwd) == 0)
		return (free_ret(nxtpwd, oldpwd, NULL, EXIT_SUCCESS));
	if (chdir(nxtpwd) == -1)
	{
		write(STDERR_FILENO, "MINI: cd: ", 10);
		perror(nxtpwd);
		return (free_ret(nxtpwd, oldpwd, NULL, EXIT_FAILURE));
	}
	return (export_pwd(nxtpwd, oldpwd));
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
