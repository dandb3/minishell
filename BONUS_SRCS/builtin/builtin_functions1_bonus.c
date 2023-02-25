/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions1_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:36:47 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/25 13:03:43 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_bonus.h"

int	builtin_pwd(void)
{
	char	*pwd;

	pwd = ft_getcwd("pwd");
	if (pwd == NULL)
		return (EXIT_FAILURE);
	ft_printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}

static int	export_pwd(char *nxtpwd, char *oldpwd)
{
	char	**cmd;
	char	*pwd;

	pwd = ft_getcwd("cd");
	if (pwd == NULL)
		return (EXIT_FAILURE);
	cmd = (char **)ft_calloc(4, sizeof(char *));
	if (cmd == NULL)
		exit(MALLOC_FAILURE);
	cmd[0] = ft_strdup("export");
	cmd[1] = ft_strjoin("OLDPWD=", oldpwd);
	cmd[2] = ft_strjoin("PWD=", pwd);
	cmd[3] = NULL;
	if (!cmd[0] || !cmd[1] || !cmd[2])
		exit(MALLOC_FAILURE);
	builtin_export(cmd);
	free_ret(cmd[0], cmd[1], cmd[2], 0);
	free(nxtpwd);
	return (free_ret(cmd, oldpwd, pwd, 0));
}

int	builtin_cd(char **cmd)
{
	char		*oldpwd;
	char		*nxtpwd;

	if (!(*(++cmd)))
	{
		nxtpwd = find_env_val("HOME");
		if (!nxtpwd)
			return ((write(STDERR_FILENO, HOME_NOT_SET, 23) & 0) | 1);
	}
	else
		nxtpwd = ft_strdup(*cmd);
	if (!nxtpwd)
		exit(MALLOC_FAILURE);
	oldpwd = ft_getcwd("cd");
	if (!oldpwd)
		return (free_ret(nxtpwd, NULL, NULL, EXIT_FAILURE));
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
	if (*str == 0)
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
