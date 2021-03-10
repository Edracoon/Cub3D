/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 13:58:18 by epfennig          #+#    #+#             */
/*   Updated: 2021/02/06 10:30:56 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_check_c(char s, char c)
{
	if (s == c)
		return (1);
	return (0);
}

int			count_char_c(const char *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && ft_check_c(s[i], c) == 1)
			i++;
		if (s[i] && ft_check_c(s[i], c) == 0)
		{
			count++;
			while (s[i] && ft_check_c(s[i], c) == 0)
				i++;
		}
	}
	return (count);
}

char		*ft_alloc_str(char const *s, char c)
{
	char	*tab;
	int		i;

	i = 0;
	while (s[i] && ft_check_c(s[i], c) == 0)
		i++;
	if ((tab = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	i = 0;
	while (s[i] && ft_check_c(s[i], c) == 0)
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	int		nb_c;
	char	**dest;

	i = 0;
	nb_c = count_char_c(s, c);
	if ((dest = (char **)malloc(sizeof(char *) * nb_c + 1)) == NULL)
		return (NULL);
	nb_c = 0;
	while (s[i])
	{
		while (s[i] && ft_check_c(s[i], c) == 1)
			i++;
		if (s[i] && ft_check_c(s[i], c) == 0)
		{
			dest[nb_c] = ft_alloc_str((s + i), c);
			nb_c++;
			while (s[i] && ft_check_c(s[i], c) == 0)
				i++;
		}
	}
	dest[nb_c] = NULL;
	return (dest);
}
