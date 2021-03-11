/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:53:36 by epfennig          #+#    #+#             */
/*   Updated: 2021/03/11 11:37:31 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				ft_strlen2(const char *str)
{
	int			i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char			*ft_strduplicate(char *src)
{
	int			i;
	char		*dest;

	i = 0;
	while (src[i] != '\0')
		i++;
	if (!(dest = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char			*ft_strcherche(const char *s, int c)
{
	char		*str;

	str = (char *)s;
	while (*str != c)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return (str);
}

char			*ft_sousstr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		j;
	char		*dest;

	i = 0;
	j = 0;
	if (!(dest = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (s[i] != '\0')
	{
		if (i >= start && j < len)
		{
			dest[j] = s[i];
			j++;
		}
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

int				get_next_line(int fd, char **line)
{
	ssize_t		ret;
	char		buff[BUFFER_SIZE + (ret = 1)];
	static char	*str = NULL;
	char		*temp;

	if (fd < 0 || fd >= 256 || !line || BUFFER_SIZE <= 0)
		return (-1);
	str == NULL ? str = ft_memalloc(1 * sizeof(char)) : NULL;
	while (!ft_strcherche(str, '\n') && (ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		temp = ft_stringjoin(str, buff);
		ft_strfree(&str);
		str = temp;
	}
	if (ret == 0)
		*line = ft_strduplicate(str);
	else if (ret > 0)
		*line = ft_sousstr(str, 0, (ft_strcherche(str, '\n') - str));
	else
		return (-1);
	temp = ft_strduplicate(str + (ft_strlen2(*line) + ((ret > 0) ? +1 : +0)));
	ft_strfree(&str);
	str = temp;
	return (ret == 0 ? 0 * ft_strfree(&str) : 1);
}
