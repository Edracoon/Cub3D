/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 10:12:57 by epfennig          #+#    #+#             */
/*   Updated: 2021/04/08 14:41:32 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int	ft_noneg(long int nb)
{
	if (nb < 0)
	{
		return (-nb);
	}
	return (nb);
}

int	ft_intlen(long int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = nb * (-1);
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	int		sign;
	char	*str;

	len = ft_intlen(n);
	if (n < 0)
		sign = -1;
	else
		sign = 1;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!(str))
		return (NULL);
	str[len] = '\0';
	len--;
	while (len >= 0)
	{
		str[len] = '0' + ft_noneg(n % 10);
		n = ft_noneg(n / 10);
		len--;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}
