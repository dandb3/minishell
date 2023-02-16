/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:03:28 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/14 20:31:24 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "parser.h"

static char	*read_here_doc(char *here_doc_end)
{
	char	*total_line;
	char	*cur_line;

	total_line = ft_strdup("");
	if (total_line == NULL)
		exit(MALLOC_FAILURE);
	cur_line = readline("< ");
	while (cur_line != NULL && ft_strcmp(here_doc_end, cur_line))
	{
		total_line = ft_strjoin_and_free(total_line, cur_line);
		total_line = ft_strjoin_and_free(total_line, "\n");
		free(cur_line);
		cur_line = readline("< ");
	}
	free(cur_line);
	return (total_line);
}

void	insert_and_pop(t_list *stack, t_tree *cur_tree, t_node *cur_token)
{
	char	*here_doc_end;

	if (cur_token->lex == LEX_COMPOUND)
	{
		cur_tree->val = copy_list(cur_token->val);
		if (cur_token->prev->lex == LEX_HERE_DOC)
		{
			del_quotes(cur_tree->val);
			here_doc_end = extract_pure_word(cur_tree->val);
			free_list(cur_tree->val, 0, LEX);
			cur_tree->val = read_here_doc(here_doc_end);
			free(here_doc_end);
		}
	}
	pop(stack);
}
