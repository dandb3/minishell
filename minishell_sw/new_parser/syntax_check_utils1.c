/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:03:28 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/19 21:17:51 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

void	syntax_init(t_node **cur_token, t_list **stack, t_list *token_list)
{
	init_heredoc_status();
	*cur_token = token_list->head->next;
	*stack = make_list(LEX);
	push(*stack, make_tree(AST_E0));
}

static char	*read_here_doc(char *here_doc_end)
{
	char	*total_line;
	char	*cur_line;

	total_line = ft_strdup("");
	if (total_line == NULL)
		exit(MALLOC_FAILURE);
	cur_line = readline("> ");
	while (cur_line != NULL && ft_strcmp(here_doc_end, cur_line))
	{
		total_line = ft_strjoin_and_free(total_line, cur_line);
		total_line = ft_strjoin_and_free(total_line, "\n");
		free(cur_line);
		cur_line = readline("> ");
	}
	free(cur_line);
	return (total_line);
}

void	here_doc_or_pop(t_list *stack, t_node **cur_token)
{
	char	*here_doc_end;

	pop_tree(stack);
	if ((*cur_token)->lex == LEX_COMPOUND \
		&& (*cur_token)->prev->lex == LEX_HERE_DOC)
	{
		del_quotes((*cur_token)->val);
		here_doc_end = extract_pure_word((*cur_token)->val);
		free_list((*cur_token)->val, 0, LEX);
		(*cur_token)->val = read_here_doc(here_doc_end);
		(*cur_token)->lex = LEX_WORD;
		free(here_doc_end);
	}
	*cur_token = (*cur_token)->next;
}
