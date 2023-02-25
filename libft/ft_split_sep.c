/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_sep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:08:38 by jdoh              #+#    #+#             */
/*   Updated: 2023/01/08 10:05:34 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char *sep, size_t s_len)
{
	size_t	idx;
	int		flag;
	size_t	word_num;

	flag = 1;
	idx = 0;
	word_num = 0;
	while (idx < s_len)
	{
		if (ft_strchr(sep, s[idx]))
			flag = 1;
		else if (flag)
		{
			word_num++;
			flag = 0;
		}
		idx++;
	}
	return (word_num);
}

static char	*make_word(size_t *word_start, char const *s, char *sep, size_t len)
{
	size_t	word_end;
	char	*word;

	while (*word_start < len && ft_strchr(sep, s[*word_start]))
		(*word_start)++;
	word_end = *word_start;
	while (word_end < len)
	{
		if (ft_strchr(sep, s[word_end]))
			break ;
		word_end++;
	}
	word = ft_substr(s, *word_start, word_end - *word_start);
	*word_start = word_end;
	return (word);
}

static char	**free_all(char **result, size_t w_idx)
{
	size_t	idx;

	idx = 0;
	while (idx < w_idx)
	{
		free(result[idx]);
		idx++;
	}
	free(result);
	return (0);
}

char	**ft_split_sep(char const *s, char *sep)
{
	size_t	s_idx;
	size_t	w_idx;
	size_t	s_len;
	size_t	word_num;
	char	**result;

	if (s == 0)
		return (0);
	s_len = ft_strlen(s);
	word_num = count_words(s, sep, s_len);
	result = (char **) malloc(sizeof(char *) * (word_num + 1));
	if (result == 0)
		return (0);
	w_idx = 0;
	s_idx = 0;
	while (w_idx < word_num)
	{
		result[w_idx] = make_word(&s_idx, s, sep, s_len);
		if (result[w_idx] == 0)
			return (free_all(result, w_idx));
		w_idx++;
	}
	result[w_idx] = 0;
	return (result);
}
