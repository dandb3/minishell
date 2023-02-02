/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:37:09 by sunwsong          #+#    #+#             */
/*   Updated: 2023/01/27 10:47:30 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// }t_list;

// libft
int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *src);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlen(const char *str);
int			ft_strcmp(const char *str1, const char *str2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strrchr(const char *s, int c);
int			ft_tolower(int c);
int			ft_toupper(int c);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		*ft_calloc(size_t count, size_t size);
char		*ft_itoa(int n);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *str, int fd);
char		**ft_split(char const *s, char c);
char		**ft_split_sep(char const *s, char *sep);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strtrim(char const *s1, char const *set);

// libft bonus
// void		ft_listadd_back(t_list **lst, t_list *new);
// void		ft_listadd_front(t_list **lst, t_list *new);
// void		ft_listclear(t_list **lst, void (*del)(void *));
// void		ft_listdelone(t_list *lst, void (*del)(void *));
// void		ft_listiter(t_list *lst, void (*f)(void *));
// t_list		*ft_listlast(t_list *lst);
// t_list		*ft_listmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
// t_list		*ft_listnew(void *content);
// int			ft_listsize(t_list *lst);

// ft_printf
long long	ft_printf_char(int ch);
long long	ft_printf_string(char *str);
long long	ft_printf_nbr(int num);
long long	ft_printf_unbr(unsigned int num);
long long	ft_printf_hex(unsigned int num, int is_upper);
long long	ft_putnbr_ptr(size_t num);
long long	ft_putnbr_base(long long nbr, int len, const char *base);
int			ft_printf(const char *format, ...);

#endif