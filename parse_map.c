/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 11:48:08 by epfennig          #+#    #+#             */
/*   Updated: 2021/04/08 15:49:05 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "cub3d.h"
#include "libft/libft.h"

void	sprite_handler(t_parse *p)
{
	int	i;
	int	j;
	int	nb;

	nb = 0;
	i = 0;
	j = 0;
	while (p->map[i][j])
	{
		j= 0;
		while (p->map[i][j])
		{
			if (p->map[i][j] == '2' && nb <= p->spr.nbspr)
			{
				p->sprite[p->spr.nbspr].x = j + 0.5;
				p->sprite[p->spr.nbspr].y = i + 0.5;
			}
			j++;
		}
		i++;
	}
}

int	find_player(t_parse *p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	p->spr.nbspr = 0;
	while (p->map[i][j])
	{
		while (p->map[i][j])
		{
			if (p->map[i][j] == 'W' || p->map[i][j] == 'E'
				|| p->map[i][j] == 'N' || p->map[i][j] == 'S')
			{
				p->dir = p->map[i][j];
				p->map[i][j] = '0';
				p->per_x = j * p->minimap + p->minimap / 2;
				p->per_y = i * p->minimap + p->minimap / 2;
			}
			if (p->map[i][j] == '2')
				p->spr.nbspr += 1;
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}

int	parse_map(t_parse *p)
{
	int i = 0;
	while (p->map[0][i])
		i++;
	p->minimap = (p->win_x / 4) / i;
	if (!find_player(p))
		return (0);
	p->sprite = malloc(sizeof(t_sprite) * p->spr.nbspr);
	if (!p->sprite)
		exit(0);
	sprite_handler(p);
	return (1);
}
