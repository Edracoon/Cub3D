/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 12:53:36 by epfennig          #+#    #+#             */
/*   Updated: 2021/03/10 15:54:56 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		len;

	if (s1 && s2)
	{
		len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
		dest = malloc(sizeof(char) * len + 1);
		if (!(dest))
			return (NULL);
		ft_strcpy(dest, (char *)s1);
		ft_strcat(dest, (char *)s2);
		return (dest);
	}
	return (NULL);
}
