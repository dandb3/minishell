/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:41:06 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/21 22:33:08 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	eof_exit(void)
{
	printf("exit\n");
	exit(get_exitcode());
}

static int	redirection_return(int red_in, int red_out, int ret)
{
	if (dup2(red_in, STDIN_FILENO) == FAILURE)
		perror_msg(NULL, 1);
	if (dup2(red_out, STDOUT_FILENO) == FAILURE)
		perror_msg(NULL, 1);
	return (ret);
}

static void	redirection_set(int *red_in, int *red_out)
{
	*red_in = dup(STDIN_FILENO);
	*red_out = dup(STDOUT_FILENO);
	if (*red_in == FAILURE || *red_out == FAILURE)
		perror_msg(NULL, 1);
}

void	print_tree(t_tree *tree) // 지우세용
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
	int		red_in;
	int		red_out;

	redirection_set(&red_in, &red_out);
	while (1)
	{
		cmd = readline("MINI$ ");
		if (!cmd)
			eof_exit();
		if (ft_strlen(cmd))
		{
			add_history(cmd);
			parse_tree = parser(cmd);
			if (parse_tree)
			{
				set_exitcode(execute(parse_tree, 0), 0);
				redirection_return(red_in, red_out, 0);
				free_tree(parse_tree);
			}
		//	system("leaks minishell");
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
// 				set_exitcode(do_builtin(cmds), 0);
// 			free_twoptr(cmds, 0);
// 		}
// 		free(cmd);
// 	}
// 	clear_history();
// 	return (0);
// }
