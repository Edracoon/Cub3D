/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:31:17 by epfennig          #+#    #+#             */
/*   Updated: 2021/01/26 11:53:23 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t count;
	size_t i;

	count = 0;
	i = 0;
	while ((char)dest[count] != '\0')
		count++;
	while ((char)src[i] != '\0' && i + 1 < n)
	{
		dest[i] = (char)src[i];
		i++;
	}
	if (i < n)
		dest[i] = '\0';
	return (ft_strlen((char *)src));
}
