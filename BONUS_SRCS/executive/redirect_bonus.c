/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:06:42 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/25 13:03:43 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_bonus.h"

static char	*copy_and_extract(t_list *list)
{
	t_list	*copied_list;
	char	*pure_str;

	copied_list = copy_list(list);
	pure_str = extract_pure_word(copied_list);
	free_list(copied_list, 0, NAME);
	return (pure_str);
}

static void	ambiguous_redirect_error(char *pure_str)
{
	write(STDERR_FILENO, SHELL, SHELL_LEN);
	write(STDERR_FILENO, pure_str, ft_strlen(pure_str));
	write(STDERR_FILENO, ": ambiguous redirect\n", 21);
	free(pure_str);
}

static char	*get_val_from_expanded_list(t_tree *cur)
{
	t_list	*compound_list;
	char	*pure_str;
	char	*val;

	if (cur->symbol == AST_HERE_DOC)
	{
		val = cur->val;
		cur->val = NULL;
		return (val);
	}
	pure_str = copy_and_extract(cur->val);
	compound_list = expand_char(cur->val);
	if (compound_list->size != 1 \
		|| compound_list->head->next->val == NULL)
	{
		ambiguous_redirect_error(pure_str);
		free_list(compound_list, 0, NAME);
		return (NULL);
	}
	free(pure_str);
	val = ft_strdup(compound_list->head->next->val);
	free_list(compound_list, 0, NAME);
	if (val == NULL)
		exit(MALLOC_FAILURE);
	return (val);
}

int	manage_redirect(t_tree *cur)
{
	char	*val;
	int		status;

	status = 0;
	if (!cur)
		return (SUCCESS);
	if (manage_redirect(cur->left_child) == 1)
		return (1);
	val = get_val_from_expanded_list(cur);
	if (val == NULL)
		return (set_exitcode(1, 1));
	if (cur->symbol == AST_REDIRECT_IN)
		status = read_file(val);
	else if (cur->symbol == AST_REDIRECT_OUT)
		status = write_file(val);
	else if (cur->symbol == AST_REDIRECT_APPEND)
		status = append_file(val);
	else if (cur->symbol == AST_HERE_DOC)
		status = here_doc(val, FALSE);
	free(val);
	return (status);
}
