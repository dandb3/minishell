/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:41:06 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/17 18:16:59 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	eof_exit(void)
{
	exit(EXIT_SUCCESS);
}

void	print_tree(t_tree *tree)
{
	if (!tree)
		return ;
	print_tree(tree->left_child);
	printf("tree->val: %s", (char *)(((t_list *)(tree->val))->head->next->val));
	print_tree(tree->right_child);
}

int	prompt(void)
{
	char	*cmd;
	t_tree	*parse_tree;

	while (1)
	{
		cmd = readline("MINI$ ");
		if (!cmd)
			eof_exit();
		if (ft_strlen(cmd))
		{
			add_history(cmd);
			parse_tree = parser(cmd);
			execute(parse_tree, 0);
			system("leaks minishell");
		}
		free(cmd);
	}
	clear_history();
	return (0);
}


// int	prompt(void)
// {
// 	char	*cmd;
// 	char	**cmds;

// 	//ft_signal();
// 	while (1)
// 	{
// 		cmd = readline("MINI$ ");
// 		if (!cmd)
// 			eof_exit();
// 		if (ft_strlen(cmd))
// 		{
// 			add_history(cmd);
// 			cmds = ft_split(cmd, ' ');
// 			if (!cmds)
// 				exit(MALLOC_FAILURE);
// 			if (*cmds)
// 			{
// 				do_builtin(cmds);
// 			}
// 			free_twoptr(cmds, 0);
// 		}
// 		free(cmd);
// 		system("leaks minishell");
// 	}
// 	clear_history();
// 	return (0);
// }
