/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 13:53:28 by epfennig          #+#    #+#             */
/*   Updated: 2021/03/10 16:40:39 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ischarset(char c, char *charset)
{
	while (*charset)
		if (*charset++ == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*dest;
	char	*src;

	src = (char *)s1;
	i = 0;
	start = 0;
	end = ft_strlen(src) - 1;
	while (src && ft_ischarset(src[end], (char *)set))
		end--;
	while (src && ft_ischarset(src[start], (char *)set))
		start++;
	if (start > end)
		dest = malloc(start - start + 1);
	else
		dest = malloc(end - start + 1);
	if (!(dest))
		return (NULL);
	while (end >= start)
		dest[i++] = src[start++];
	dest[i] = '\0';
	return (dest);
}
