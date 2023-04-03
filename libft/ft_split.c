/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-smed <sde-smed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:33:24 by samy              #+#    #+#             */
/*   Updated: 2022/11/30 10:55:42 by sde-smed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_words(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str)
			count++;
		while (*str && !(*str == c))
			str++;
	}
	return (count);
}

static char	*set_words(char *str, char c)
{
	char	*copy;
	int		size;
	int		i;

	i = 0;
	size = 0;
	while (!(str[size] == c) && str[size])
		size ++;
	copy = malloc(sizeof(char) * (size + 1));
	if (!copy)
		return (0);
	while (i < size)
	{
		copy[i++] = *str;
		str++;
	}
	copy[size] = 0;
	return (copy);
}

static char	**free_tab(char **tab, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
		free (tab[i++]);
	free (tab);
	return (0);
}

static char	**asign(char *str, char c, char **tab_strs)
{
	char	*tmp;
	int		i;

	i = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str)
		{
			tmp = set_words(str, c);
			if (!tmp)
				return (free_tab(tab_strs, i));
			tab_strs[i++] = tmp;
		}
		while (*str && *str != c)
			str++;
	}
	tab_strs[i] = 0;
	return (tab_strs);
}

char	**ft_split(const char *s, char c)
{
	char	**tab_strs;
	char	*str;

	if (!s)
		return (0);
	str = (char *)s;
	tab_strs = malloc(sizeof(char *) * (nb_words(str, c) + 1));
	if (!tab_strs)
		return (0);
	return (asign(str, c, tab_strs));
}
