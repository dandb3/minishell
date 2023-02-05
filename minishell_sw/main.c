/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:32:49 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/02 11:14:00 by sunwsong         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	extern char	**environ;
	char		*a;
	char		arr[102340];
	t_list		*env_list;
	t_list		*token_list;

//	atexit(leaks);
	(void) ac;
	(void) av;
	ft_signal();
	ft_terminal();
	env_list = make_envlist(envp);
	prompt(env_list);
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