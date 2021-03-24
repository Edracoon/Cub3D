/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 10:56:45 by epfennig          #+#    #+#             */
/*   Updated: 2021/03/24 14:44:01 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_stringjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	str = (char *)malloc(ft_slen2(s1) + ft_slen2(s2) + 1);
	if (s1 == NULL || s2 == NULL || !(str))
		return (NULL);
	str[0] = '\0';
	i = -1;
	j = 0;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_strfree(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

char	*ft_memalloc(size_t size)
{
	char		*str;
	size_t		i;

	i = 0;
	str = malloc(size);
	if (!(str))
		return (NULL);
	while (i < size)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}

char	*verif_ret(char *str, int ret)
{
	if (ret == 0)
		return (ft_strdupl(str));
	else if (ret > 0)
		return (ft_sousstr(str, 0, (ft_strcherche(str, '\n') - str)));
	else
		return (NULL);
}

int	ft_tern(int a, int fals, int part, char **str)
{
	if (part == 1)
	{
		if (a > 0)
			return (1);
		else
			return (fals);
	}
	if (part == 2)
	{
		if (a == 0)
			return (0 * ft_strfree(str));
		else
			return (fals);
	}
	return (0);
}
