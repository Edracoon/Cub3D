/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 11:48:08 by epfennig          #+#    #+#             */
/*   Updated: 2021/03/25 16:39:16 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "cub3d.h"
#include "libft/libft.h"

int	find_player(t_parse *p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (p->map[i][j])
	{
		while (p->map[i][j])
		{
			if (p->map[i][j] == 'W' || p->map[i][j] == 'E'
				|| p->map[i][j] == 'N' || p->map[i][j] == 'S')
			{
				p->map[i][j] = '0';
				p->per_x = j * minimap;
				p->per_y = i * minimap;
				return (1);
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}

int	parse_map(t_parse *p)
{
	if (!find_player(p))
		return (0);
	return (1);
}