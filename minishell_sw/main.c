/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:32:49 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/18 17:00:36 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *abc[100] = {
	"LEX_SINGLE_QUOTE",
	"LEX_DOUBLE_QUOTE",
	"LEX_REDIRECT_IN",
	"LEX_REDIRECT_OUT",
	"LEX_HERE_DOC",
	"LEX_REDIRECT_APP",
	"LEX_PIPE",
	"LEX_ENV",
	"LEX_AND",
	"LEX_OR",
	"LEX_WILD",
	"LEX_WORD",
	"LEX_PARENTHESIS_OPEN",
	"LEX_PARENTHESIS_CLOSE",
	"LEX_WHIT"
};

void	print_tokenlist(t_list *token_list)
{
	t_node	*cur;

	cur = token_list->head->next;
	while (cur->next)
	{
		printf("string: %s, lex: %s\n", (char *)(cur->val), abc[cur->lex]);
		cur = cur->next;
	}
}

// int	main(void)
// {
// 	char	*wild;
// 	char	*res;

// 	wild = (char *)malloc(sizeof(char) * 1000000);
// 	scanf(" %s", wild);
// 	res = wildcard(wild, ".");
// 	printf("res: %s\n", res);
// 	return (0);
// }

int	main(int ac, char **av)
{
	extern char	**environ;

//	atexit(leaks);
	(void) ac;
	(void) av;
	g_env_list = make_envlist(environ);
	ft_signal();
	ft_terminal();
	prompt();
	return (0);
}

// void	leaks(void)
// {
// 	system("leaks minishell");
// }

// int	main(int ac, char **av, char **envp)
// {
// 	t_list	*env_list;

// 	atexit(leaks);
// 	(void) ac;
// 	(void) av;
// 	ft_signal();
// 	(void) envp;
// 	env_list = make_envlist(envp);
// 	prompt(env_list);
// 	return (0);
// }