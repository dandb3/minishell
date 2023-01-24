/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:36:47 by sunwsong          #+#    #+#             */
/*   Updated: 2023/01/24 18:01:50 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 100000);
	if (pwd == NULL)
		return (FALSE);
	ft_printf("%s\n", pwd);
	free(pwd);
	return (TRUE);
}

int	builtin_cd(char *str, char **envp)
{
	char	*pwd;

	pwd = NULL;
	if (!str)
	{
		while (*envp && !pwd)
		{
			if (ft_strlen(*envp) >= 5 && !ft_strncmp(*envp, "HOME=", 5))
				pwd = ft_substr(*envp, 5, ft_strlen(*envp) - 5);
			++envp;
		}
		if (!pwd)
		{
			ft_printf("HOME not set\n");
			return (FALSE);
		}
	}
	if (str)
		pwd = str;
	if (chdir(str) == -1)
	{
		ft_printf("MINI: cd: %s: No such file or directory\n", str);
		return (FALSE);
	}
	return (TRUE);
}

int	main(int ac, char **av, char **envp)
{
	char	str[15];

	(void) ac;
	(void) av;
	(void) envp;
	builtin_pwd();
	//builtin_cd(NULL, envp);
	// chdir("/");
	// builtin_pwd();
	while (1)
	{
		scanf("%s", str);
		builtin_cd(str, envp);
		builtin_pwd();
	}
	return (0);
}
