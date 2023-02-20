/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:03:28 by jdoh              #+#    #+#             */
/*   Updated: 2023/02/20 19:24:56 by jdoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

void	syntax_init(t_node **cur_token, t_list **stack, t_list *token_list)
{
	set_heredoc_status(0);
	*cur_token = token_list->head->next;
	*stack = make_list(LEX);
	push(*stack, make_tree(AST_E0));
}

static void	sigaction_init(struct sigaction *sa)
{
	ft_memset(sa, 0, sizeof(sa));
	sa->__sigaction_u.__sa_handler = heredoc_handler;
	sa->sa_flags = 0;
	sigaddset(&sa->sa_mask, SIGINT);
}

static char	*read_here_doc(char *here_doc_end)
{
	char	buf[1025];
	char	*total_line;
	ssize_t	read_len;

	buf[1024] = '\0';
	total_line = ft_strdup("");
	if (total_line == NULL)
		exit(MALLOC_FAILURE);
	read_len = read(STDIN_FILENO, buf, 1024);
	while (read_len > 0 && ft_strchr(buf, '\n') == NULL \
		&& ft_strcmp(buf, here_doc_end))
	{
		total_line = ft_strjoin_and_free(total_line, buf);
		read_len = read(STDIN_FILENO, buf, 1024);
	}
	if (read_len == FAILURE)
		set_heredoc_status(1);
	return (total_line);
}

void	here_doc_or_pop(t_list *stack, t_node **cur_token)
{
	char				*here_doc_end;
	struct sigaction	sa;
	struct sigaction	old_sa;

	pop_tree(stack);
	if ((*cur_token)->lex == LEX_COMPOUND \
		&& (*cur_token)->prev->lex == LEX_HERE_DOC)
	{
		sigaction_init(&sa);
		sigaction(SIGINT, &sa, &old_sa);
		del_quotes((*cur_token)->val);
		here_doc_end = extract_pure_word((*cur_token)->val);
		free_list((*cur_token)->val, 0, LEX);
		(*cur_token)->val = read_here_doc(here_doc_end);
		(*cur_token)->lex = LEX_WORD;
		free(here_doc_end);
		sigaction(SIGINT, &old_sa, NULL);
	}
	*cur_token = (*cur_token)->next;
}
