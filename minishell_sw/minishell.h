/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:33:52 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/14 14:16:58 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> // 지우세용
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# include "libft/libft.h"

# define MALLOC_FAILURE 2

enum	e_bool
{
	FALSE = 0,
	TRUE
};

typedef enum e_lex
{
	LEX_SINGLE_QUOTE,
	LEX_DOUBLE_QUOTE,
	LEX_ENV,
	LEX_WILD,
	LEX_WORD,
	LEX_WHITE,
	LEX_COMPOUND,
	LEX_OR,
	LEX_AND,
	LEX_PIPE,
	LEX_PARENTHESIS_OPEN,
	LEX_PARENTHESIS_CLOSE,
	LEX_REDIRECT_IN,
	LEX_REDIRECT_OUT,
	LEX_HERE_DOC,
	LEX_REDIRECT_APP
}			t_lex;

enum e_sbool
{
	FAILURE = -1,
	SUCCESS
};

typedef enum e_type
{
	ENV = 0,
	LEX = 1,
	NAME = 0,
	COMPOUND = 2
}	t_type;

typedef struct s_node
{
	void			*val;
	struct s_node	*next;
	struct s_node	*prev;
	t_lex			lex;
}	t_node;

typedef struct s_env
{
	char			*key;
	char			*val;
}	t_env;

typedef struct s_list
{
	struct s_node	*head;
	struct s_node	*tail;
	int				size;
	t_type			type;
}	t_list;

t_list		*g_env_list;

/*--------------------------------  main  ---------------------------------*/
int			ft_signal(void);
int			ft_terminal(void);
char		*wildcard(char *wstr, char *path);

/*-------------------------------- builtin --------------------------------*/
int			do_builtin(char **cmds);
int			prompt(void);

/*--------------------------- doubly linked list --------------------------*/
t_list		*make_list(t_type type);
t_list		*copy_list(t_list *list);
void		*copy_val(t_node *node);
void		push_node(t_node *node, t_list *list);
void		insert_node(t_node *insert_point, t_node *node);
long long	free_nodes(t_list *list, long long ret, t_type type);
long long	free_list(t_list *list, long long ret, t_type type);
void		sort_list(t_list *list);

/*------------------------------- node list -------------------------------*/
t_node		*make_node(void *val, t_lex lex);
void		del_node(t_node *node, t_type type);
void		free_node(t_node *node, t_type type);

/*--------------------------------- utils ---------------------------------*/
long long	free_ret(void *obj1, void *obj2, void *obj3, long long ret);
long long	free_twoptr(char **ptr, long long ret);
char		*ft_strjoin_and_free(char *s1, char *s2);
void		error_msg(char *str, int status);
void		perror_msg(char *str, int status);

/*------------------------------- env utils -------------------------------*/
size_t		get_envlen(const char *str);
int			check_valid_keyname(const char *str);
t_env		*make_env(const char *str, int to_check);
int			push_environ(t_env *env, t_node *cur);
int			print_envlist(const char *pre);
t_list		*make_envlist(char **envp);
char		**env_to_char(void);
void		sort_envlist(t_list *env_list);
char		*find_env_val(const char *key);
short		set_exitcode(int exit_code, long long ret);
short		get_exitcode(void);

/*lexer*/
int			make_token_list(t_list **token_list, char const *str);

#endif