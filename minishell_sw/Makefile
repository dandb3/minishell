# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 19:25:02 by jdoh              #+#    #+#              #
#    Updated: 2023/02/16 20:43:02 by sunwsong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
SRCS_M		=	main.c prompt.c minishell_utils1.c minishell_utils2.c terminal.c \
				builtin/builtin_functions1.c builtin/builtin_functions2.c \
				builtin/builtin.c env/env_utils1.c env/env_utils2.c env/env_utils3.c\
				doublylinkedlist1.c doublylinkedlist2.c doublylinkedlist3.c\
				signal.c wildcard/wildcard.c \
				new_parser/del_unused.c new_parser/get_pseudo_token.c \
				new_parser/group_compound.c new_parser/lexer.c new_parser/make_ast_utils1.c \
				new_parser/make_ast_utils2.c new_parser/make_ast.c new_parser/parser_utils1.c \
				new_parser/parser_utils2.c new_parser/parser.c new_parser/production.c \
				new_parser/pseudo_expand_env.c new_parser/stack.c \
				new_parser/syntax_check_utils.c new_parser/syntax_check.c \
				new_parser/syntax_error.c new_parser/tree.c \
				executive/execute.c executive/execute_utils2.c executive/open_file.c \
				executive/execute.h executive/expand.c executive/redirect.c \
				executive/execute_pipe.c executive/here_doc.c \
				executive/execute_utils1.c executive/init_pipe.c \
				wildcard/wildcard.c wildcard/wildcard_utils.c wildcard/discriminate.c
				
OBJS_M		=	$(SRCS_M:.c=.o)
HEADER_M	=	minishell builtin/builtin executive/execute wildcard/wildcard \
				new_parser/parser

# SRCS_B		=	main_bonus.c init_bonus.c error_bonus.c parsing_bonus.c \
# 				pipex_bonus.c process_bonus.c get_next_line_bonus.c \
# 				fileopen_bonus.c
# OBJS_B		=	$(SRCS_B:.c=.o)
# HEADER_B	=	pipex_bonus.h

LIBFT		=	libft/libft.a
LIBFT_DIR	=	libft

RL_LINK_FLAG	= -lreadline -L $(HOME)/goinfre/.brew/Cellar/readline/8.2.1/lib
RL_COMP_FLAG	= -I $(HOME)/goinfre/.brew/Cellar/readline/8.2.1/include

CFLAGS		=	-Werror -Wextra -Wall
BONUS_MODE	=	$(findstring bonus, $(MAKECMDGOALS))

ifeq (bonus, $(BONUS_MODE))
	SRCS	=	$(SRCS_B)
	OBJS	=	$(OBJS_B)
	HEADER	=	$(HEADER_B)
else
	SRCS	=	$(SRCS_M)
	OBJS	=	$(OBJS_M)
	HEADER	=	$(HEADER_M)
endif

all			:	$(NAME)
bonus		:	$(NAME)

$(NAME)		:	$(OBJS)
	$(CC) $(CFLAGS) $(RL_LINK_FLAG) $(OBJS) libft.a -lreadline -o $@
	

# $(NAME)		:	$(OBJS) $(LIBFT)
# 	$(CC) $(CFLAGS) $(OBJS) -L $(LIBFT_DIR) -lft -lreadline -o $@

$(LIBFT)	:
	make -C $(LIBFT_DIR) bonus

%.o			:	%.c
	$(CC) $(CFLAGS) $(RL_COMP_FLAG) -c $< -o $@

clean		:
	rm -rf $(OBJS_M) $(OBJS_B)
#	make -C $(LIBFT_DIR) fclean

fclean		:	clean
	rm -rf $(NAME)

re			:
	make fclean
	make all

.PHONY		:	all bonus clean fclean re