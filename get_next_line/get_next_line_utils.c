/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 10:56:45 by epfennig          #+#    #+#             */
/*   Updated: 2021/03/11 11:32:45 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char			*ft_stringjoin(char const *s1, char const *s2)
{
	int			i;
	int			j;
	char		*str;

	if (s1 == NULL || s2 == NULL || !(str = (char *)malloc(ft_strlen2(s1)
		+ ft_strlen2(s2) + 1)))
		return (NULL);
	str[0] = '\0';
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

int				ft_strfree(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

char			*ft_memalloc(size_t size)
{
	char		*str;
	size_t		i;

	i = 0;
	if (!(str = malloc(size)))
		return (NULL);
	while (i < size)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}
