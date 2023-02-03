/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:32:49 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/03 19:30:35 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokenlist(t_list *token_list)
{
	t_node	*cur;

	cur = token_list->head->next;
	while (cur->next)
	{
		printf("string: %s, lex: %d\n", (char *)(cur->val), cur->lex);
		cur = cur->next;
	}
	printf("end!\n");
}

int	main(void)
{
	extern char	**environ;
	t_list		*env_list;
	t_list		*token_list;
	char		str[10000];

	env_list = make_envlist(environ);
	token_list = NULL;
	scanf(" %s", str);
	make_token_list(&token_list, env_list, str);
	print_tokenlist(token_list);
	exit(0);
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