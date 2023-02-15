# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 19:25:02 by jdoh              #+#    #+#              #
#    Updated: 2023/02/15 20:40:14 by jdoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
SRCS_M		=	del_unused.c get_pseudo_token.c group_compound.c lexer.c make_ast_utils1.c \
				make_ast_utils2.c make_ast.c parser_utils1.c parser_utils2.c parser.c production.c \
				pseudo_expand_env.c stack.c syntax_check_utils.c syntax_check.c syntax_error.c tree.c
SRCS		=	$(addprefix new_parser/, $(SRCS_M))
ELEARN		=	doublylinkedlist1.c doublylinkedlist2.c doublylinkedlist3.c libft.a minishell_utils.c test.c \
				env/env_utils1.c env/env_utils2.c env/env_utils3.c

all : $(NAME)

$(NAME) :
	$(CC) $(SRCS) $(ELEARN) -lreadline -g -o testshell