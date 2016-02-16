/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 21:07:03 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/02 12:03:42 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

static int	ft_nb_words(char const *s, char c)
{
	int		nb_words;
	int		first_word;
	int		i;
	int		already;

	nb_words = 0;
	first_word = 0;
	i = 0;
	already = 0;
	while (s[i])
	{
		if (first_word == 0 && s[i] != c)
			first_word = 1;
		if (already == 1 && s[i] != c)
		{
			nb_words++;
			already = 0;
		}
		if (s[i] == c && already == 0 && first_word == 1)
			already = 1;
		i++;
	}
	if (first_word == 1)
		nb_words++;
	return (nb_words);
}

static char	*ft_get_next_word(char const *s, char c, int *i)
{
	unsigned int	start;

	while (s[*i] && s[*i] == c)
		(*i)++;
	start = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	return (ft_strsub(s, start, *i - start));
}

char		**ft_strsplit(char const *s, char c)
{
	int		nb_words;
	int		crt_nb;
	int		i;
	char	**res;

	if (s == NULL)
		return (NULL);
	nb_words = ft_nb_words(s, c);
	if (!(res = (char**)malloc(sizeof(char*) * (nb_words + 1))))
		return (NULL);
	res[nb_words] = 0;
	crt_nb = 0;
	i = 0;
	while (crt_nb < nb_words)
	{
		res[crt_nb] = ft_get_next_word(s, c, &i);
		crt_nb++;
	}
	return (res);
}
