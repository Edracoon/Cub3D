/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:53:36 by epfennig          #+#    #+#             */
/*   Updated: 2021/03/24 14:22:13 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_slen2(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdupl(char *src)
{
	int		i;
	char	*dest;

	i = 0;
	while (src[i] != '\0')
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	if (!(dest))
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

char	*ft_strcherche(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != c)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return (str);
}

char	*ft_sousstr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		j;
	char		*dest;

	i = 0;
	j = 0;
	dest = (char *)malloc(sizeof(char) * len + 1);
	if (!(dest))
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

int	get_next_line(int fd, char **line)
{
	static char	*str;
	char		*temp;
	char		buff[BUFFER_SIZE + 1];
	ssize_t		ret;

	ret = 1;
	if (fd < 0 || fd >= 256 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (str == NULL)
		str = ft_memalloc(1 * sizeof(char));
	while (!ft_strcherche(str, '\n') && ret > 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		buff[ret] = '\0';
		temp = ft_stringjoin(str, buff);
		ft_strfree(&str);
		str = temp;
	}
	*line = verif_ret(str, ret);
	if (*line == NULL)
		return (-1);
	temp = ft_strdupl(str + (ft_slen2(*line) + ft_tern(ret, 0, 1, &str)));
	ft_strfree(&str);
	str = temp;
	return (ft_tern(ret, 1, 2, &str));
}
