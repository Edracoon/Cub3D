/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:03:22 by epfennig          #+#    #+#             */
/*   Updated: 2021/03/31 16:57:49 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "cub3d.h"
#include "libft/libft.h"

void	draw_ceiling(t_parse *p)
{
	int y = 0;

	while (y < p->drawstart)
	{
		my_mlx_pixel_put(p, p->raycastx, y++, p->ceil_color);
	}
}

void	draw_floor(t_parse *p)
{
	int y = p->win_y;

	while (y > p->drawend)
	{
		my_mlx_pixel_put(p, p->raycastx, y--, p->floor_color);
	}
}

void	draw_line(t_parse *p)
{
	draw_ceiling(p);
	int y = p->drawend;
	int color = 0x00303030;
	if (p->side == 1)
		color = color / 2;
	while (y >= p->drawstart)
	{
		my_mlx_pixel_put(p, p->raycastx, y--, color);
	}
	draw_floor(p);
}

void	calculate_wall_dist(t_parse *p)
{
	// ici on va prendre la distance entre le plan de camera du joueur et du mur pour eviter l'effet
	// fisheye si on prends la distance euclidienne entre la position du joueur et le mur
	// on calcule donc la distance perpendiculaire
	if (p->side == 0)
		p->walldist = ((double)p->mapx - p->dper_x + (1 - (double)p->stepx) / 2) / p->raydirx;
	else
		p->walldist = ((double)p->mapy - p->dper_y + (1 - (double)p->stepy) / 2) / p->raydiry;
	p->lineheight = (int)(p->win_y / (p->walldist));
	p->drawstart = -p->lineheight / 2 + p->win_y / 2;
	if (p->drawstart < 0)
		p->drawstart = 0;
	p->drawend = p->lineheight / 2 + p->win_y / 2;
	if (p->drawend >= p->win_y)
		p->drawend = p->win_y - 1;
	draw_line(p);
}

void	ft_hit_wall(t_parse *p)
{
	// algo DDA
	while(p->hit == 0)
	{
		// on saute d'un carré de la map a un autre, dans la direction x ou y
		if (p->sidedistx < p->sidedisty)
		{
			p->sidedistx += p->deltadistx;
			p->mapx += p->stepx;
			p->side = 0;
		}
		else
		{
			p->sidedisty += p->deltadisty;
			p->mapy += p->stepy;
			p->side = 1;
		}
		// on check si le rayon a touché un mur de la map
		// printf("mapx = %i | mapy = %i", p->mapx, p->mapy);
		if (p->map[p->mapy][p->mapx] == '1')
			p->hit = 1;
	}
	calculate_wall_dist(p);
}

void	init_delta(t_parse *p)
{
	if (p->raydiry == 0)
		p->deltadistx = 0;
	else if (p->raydiry == 1)
		p->deltadistx = 1;
	else
		p->deltadistx = sqrt(1 + (p->raydiry * p->raydiry) / (p->raydirx * p->raydirx));
	if (p->raydirx == 0)
		p->deltadisty = 0;
	else if (p->raydirx == 1)
		p->deltadisty = 1;
	else
		p->deltadisty =  sqrt(1 + (p->raydirx * p->raydirx) / (p->raydiry * p->raydiry));
}

void	ft_init2(t_parse *p)
{
	p->camx = 2 * p->raycastx / (double)p->win_x - 1;
	p->raydirx = p->dirx + p->planex * p->camx;
	p->raydiry = p->diry + p->planey * p->camx;
	p->mapx = (int)(p->dper_x);
	p->mapy = (int)(p->dper_y);
	p->hit = 0;
	init_delta(p);
}

void	raycasting_main(t_parse *p)
{
	p->raycastx = 0;
	while (p->raycastx < p->win_x)
	{
		ft_init2(p);
		//printf("delx %f\n", p->deltadistx);
		//printf("dely %f\n", p->deltadisty);
		//printf("wall dist %f\n", p->walldist);
		//printf("sidedistx %f\n", p->sidedistx);
		//printf("sidedisty %f\n", p->sidedisty);
		if (p->raydirx < 0)
		{
			p->stepx = -1;
			p->sidedistx = (p->dper_x - p->mapx) * p->deltadistx;
		}
		else
		{
			p->stepx = 1;
			p->sidedistx = (p->mapx + 1.0 - p->dper_x) * p->deltadistx;
		}
		if (p->raydiry < 0)
		{
			p->stepy = -1;
			p->sidedisty = (p->dper_y - p->mapy) * p->deltadisty;
		}
		else
		{
			p->stepy = 1;
			p->sidedisty = (p->mapy + 1.0 - p->dper_y) * p->deltadisty;
		}
		ft_hit_wall(p);
		p->raycastx++;
	}
}
