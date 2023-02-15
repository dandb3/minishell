# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/19 17:38:04 by sunwsong          #+#    #+#              #
#    Updated: 2023/02/15 20:39:30 by jdoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= 	ft_isalpha.c ft_isdigit.c\
			ft_isalnum.c ft_isascii.c\
			ft_isprint.c ft_strlen.c\
			ft_memset.c ft_bzero.c\
			ft_memcpy.c ft_memmove.c\
			ft_strlcpy.c ft_strlcat.c\
			ft_toupper.c ft_tolower.c\
			ft_strchr.c ft_strrchr.c\
			ft_strncmp.c ft_memchr.c\
			ft_memcmp.c ft_strnstr.c\
			ft_atoi.c ft_strdup.c\
			ft_calloc.c ft_substr.c\
			ft_strjoin.c ft_strtrim.c\
			ft_split.c ft_itoa.c\
			ft_strmapi.c ft_striteri.c\
			ft_putchar_fd.c ft_putstr_fd.c\
			ft_putnbr_fd.c ft_putendl_fd.c\
			ft_printf.c ft_printf_tools.c putnbr_tools.c\
			ft_putnbr_fd.c ft_strcmp.c ft_split_sep.c

OBJS	= ${SRCS:.c=.o}

CFLAGS	= #-Wall -Wextra -Werror

NAME	= libft.a

all:	${NAME}
	
clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

bonus: ${NAME}

${NAME}:	${OBJS}
		ar -cr ${NAME} ${OBJS}

%.o : %.c
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

.PHONY: all clean fclean re
