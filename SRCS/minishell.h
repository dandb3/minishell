/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:33:52 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/25 13:26:31 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define MALLOC_FAILURE 2
# define SHELL "MINI: "
# define SHELL_LEN 6

enum	e_bool
{
	FALSE = 0,
	TRUE
};

typedef enum e_lex
{
	LEX_UNUSED = -1,
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

typedef enum e_symbol
{
	AST_UNUSED = -1,
	AST_E0,
	AST_E1,
	AST_E2,
	AST_E3,
	AST_E4,
	AST_E5,
	AST_E6,
	AST_E7,
	AST_E8,
	AST_COMPOUND,
	AST_OR,
	AST_AND,
	AST_PIPE,
	AST_PARENTHESES_OPEN,
	AST_PARENTHESES_CLOSE,
	AST_REDIRECT_IN,
	AST_REDIRECT_OUT,
	AST_HERE_DOC,
	AST_REDIRECT_APPEND,
	AST_EOF,
	AST_EPSILON,
	AST_PARENTHESESES,
	AST_COMMAND
}	t_symbol;

enum e_sbool
{
	FAILURE = -1,
	SUCCESS
};

typedef enum e_type
{
	TYPE_UNUSED = -1,
	ENV = 0,
	LEX = 1,
	NAME = 1,
	COMPOUND = 2
}	t_type;

enum e_signal_state
{
	SG_RUN = 0,
	SG_STOP,
	SG_CHILD
};

/**
 * doubly-linked list의 elem에 해당
 * @val: 실제 정보가 담겨있는 포인터
 * @lex: token이 어떤 lexeme에 해당하는지
*/
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

/**
 * doubly-linked list를 관리하는 구조체
 * @head: head node(NULL node)를 가리킴
 * @tail: tail node(NULL node)를 가리킴
 * @size: list의 크기
 * @type: compound type인지 lex type 인지... 를 나타냄
*/
typedef struct s_list
{
	struct s_node	*head;
	struct s_node	*tail;
	int				size;
	t_type			type;
}	t_list;

typedef struct s_tree
{
	struct s_tree	*left_child;
	struct s_tree	*right_child;
	void			*val;
	t_symbol		symbol;
}	t_tree;

t_list		*g_env_list;

/*--------------------------------  main  ---------------------------------*/
int			ft_signal(void);
int			ft_terminal(void);
t_list		*wildcard(char *wstr, size_t wlen);
t_tree		*parser(char const *input);
void		prompt(void);
int			execute(t_tree *cur, int prev_status);

/*-------------------------------- builtin --------------------------------*/
int			do_builtin(char **cmd);

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
t_node		*make_null_value_node(t_lex lex);
void		del_node(t_node *node, t_type type);
void		free_node(t_node *node, t_type type);

/*--------------------------------- utils ---------------------------------*/
long long	free_ret(void *obj1, void *obj2, void *obj3, long long ret);
long long	free_twoptr(char **ptr, long long ret);
char		*strjoin_and_free(char *s1, char *s2);
void		error_msg(char *str, int status);
void		perror_msg(char *str, int status);
char		*extract_pure_word(t_list *compound_list);
void		print_err(char const *str1, char const *str2, char const *str3);
char		*ft_getcwd(const char *cmd);

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
long long	set_exitcode(int exit_code, long long ret);
int			get_exitcode(void);

/*lexer*/
int			make_token_list(t_list **token_list, char const *str);
/*-------------------------------- signal ---------------------------------*/
void		set_signal(int mode);

/*-------------------------------- ...... ---------------------------------*/
void		free_tree(t_tree *root);

#endif
