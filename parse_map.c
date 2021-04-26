/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 11:48:08 by epfennig          #+#    #+#             */
/*   Updated: 2021/04/26 12:18:12 by epfennig         ###   ########.fr       */
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
	printf("p->spr.nbspr = %i\n", p->spr.nbspr);
	return (0);
}

void	sprite_handler(t_parse *p)
{
	int	i;
	int	j;
	int	nb;

	nb = 0;
	i = 0;
	j = 0;
	while (i <= p->spr.nbspr)
	{
		p->sprite[i].x = 0;
		p->sprite[i].x = 0;
		i++;
	}
	i = 0;
	while (p->map[i][j])
	{
	 	while (p->map[i][j])
	 	{
	 		if (p->map[i][j] == '2' && nb < p->spr.nbspr)
	 		{
				p->sprite[nb].x = (double)j + 0.5;
				p->sprite[nb].y = (double)i + 0.5;
				printf("posx %i = %f\n", nb, p->sprite[nb].x);
				printf("posy %i = %f\n", nb, p->sprite[nb].y);
	 			nb++;
	 		}
	 		j++;
	 	}
		i++;
		j = 0;
	}
}

void	init_var_spr(t_parse *p)
{
	p->spr.spritex = 0;
	p->spr.spritey = 0;
	p->spr.texture = 0;
	p->spr.invdet = 0;
	p->spr.transformx = 0;
	p->spr.transformy = 0;
	p->spr.spritescreenx = 0;
	p->spr.spriteheight = 0;
	p->spr.spritewidht = 0;
	p->spr.drawstartx = 0;
	p->spr.drawstarty = 0;
	p->spr.drawendx = 0;
	p->spr.drawendy = 0;
}

void	init_sprite(t_parse *p)
{
	p->spr.spriteord = malloc(sizeof(int) * p->spr.nbspr);
	p->spr.spritedist = (double *)malloc(sizeof(double) * p->spr.nbspr);
	if (!(p->spr.spriteord) || !(p->spr.spritedist))
		exit(0);
	p->spr.zbuffer = (double *)malloc(sizeof(double) * p->win_x);
	if (!(p->spr.zbuffer))
		exit(0);
	p->sprite = (t_sprite *)malloc(sizeof(t_sprite) * (p->spr.nbspr + 1));
	if (!p->sprite)
		exit(0);
	init_var_spr(p);
}

int	parse_map(t_parse *p)
{
	int i;

	i = 0;
	init_sprite(p);
	while (p->map[0][i])
		i++;
	p->minimap = (p->win_x / 4) / i;
	find_player(p);
	sprite_handler(p);
	return (1);
}
