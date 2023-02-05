/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:36:47 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/02 18:19:57 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <errno.h>

int	builtin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, UINT32_MAX);
	if (pwd == NULL)
		return (FALSE);
	ft_printf("%s\n", pwd);
	free(pwd);
	return (TRUE);
}

int	builtin_cd(char **cmds)
{
	char		*str;

	if (!(*(++cmds)))
	{
		ft_printf("cd: no arguments\n");
		return (EXIT_FAILURE);
	}
	if (chdir(*cmds) == -1)
	{
		str = ft_strjoin("MINI: cd: ", *cmds);
		if (!str)
			exit(EXIT_FAILURE);
		perror(str);
		return (EXIT_FAILURE);
	}
	return (TRUE);
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
