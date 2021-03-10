/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 20:30:23 by epfennig          #+#    #+#             */
/*   Updated: 2021/02/06 14:45:40 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9')
			|| ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
		return (1);
	else
		return (0);
}
