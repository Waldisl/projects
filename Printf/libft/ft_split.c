/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msunspot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 01:22:04 by msunspot          #+#    #+#             */
/*   Updated: 2020/11/19 15:19:43 by msunspot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_words(char const *s, char c)
{
	int		i;
	int		w;

	w = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			w++;
		i++;
	}
	return (w);
}

static int		words_len(char const *s, char c)
{
	int		len;

	len = 0;
	while (s[len] != c && s[len] != '\0')
	{
		len++;
	}
	return (len);
}

static void		*ft_clean(char **arrstr, int word)
{
	while (word >= 0)
	{
		free(arrstr[word--]);
	}
	free(arrstr);
	return (NULL);
}

static char		**ft_new(char const *s, int words, char c, char **arrstr)
{
	int		i;
	int		j;
	int		len;

	i = -1;
	while (++i < words)
	{
		while (*s == c)
			s++;
		len = words_len(s, c);
		if (!(arrstr[i] = (char *)malloc(sizeof(char) * (len + 1))))
			return (ft_clean(arrstr, i));
		j = 0;
		while (j < len)
			arrstr[i][j++] = *s++;
		arrstr[i][j] = '\0';
	}
	arrstr[i] = NULL;
	return (arrstr);
}

char			**ft_split(char const *s, char c)
{
	char	**arrstr;
	int		words;

	if (!s)
		return (NULL);
	words = ft_words(s, c);
	if (!(arrstr = (char **)malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	arrstr = ft_new(s, words, c, arrstr);
	return (arrstr);
}
