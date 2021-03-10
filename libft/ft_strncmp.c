/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:30:32 by epfennig          #+#    #+#             */
/*   Updated: 2021/01/26 11:53:27 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s10;
	unsigned char	*s20;

	i = 0;
	s10 = (unsigned char *)s1;
	s20 = (unsigned char *)s2;
	while ((s10[i] || s20[i]) && i < n)
	{
		if (s10[i] != s20[i])
			return (s10[i] - s20[i]);
		i++;
	}
	return (0);
}
