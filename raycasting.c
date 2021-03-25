/* ************************************************************************** */
/*																																						*/
/*																												:::		  ::::::::   */
/*   raycasting.c																		   :+:		  :+:		:+:   */
/*																										+:+ +:+				 +:+		 */
/*   By: epfennig <epfennig@student.42.fr>				  +#+  +:+		   +#+				*/
/*																								+#+#+#+#+#+   +#+				   */
/*   Created: 2021/03/23 10:40:28 by epfennig				  #+#		#+#						 */
/*   Updated: 2021/03/25 12:50:01 by epfennig				 ###   ########.fr		   */
/*																																						*/
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "cub3d.h"
#include "libft/libft.h"

void	draw_line(t_parse *p)
{
	int color = 240;

	while (p->drawend >= p->drawstart)
	{
		my_mlx_pixel_put(p, p->raycastx, p->drawend--, color);
	}
}

void	calculate_wall_dist(t_parse *p)
{
	// ici on va prendre la distance entre le plan de camera du joueur et du mur pour eviter l'effet
	// fisheye si on prends la distance euclidienne entre la position du joueur et le mur
	// on calcule donc la distance perpendiculaire
	if (p->side == 0)
		p->walldist = (p->mapx - p->dper_x + (1 - p->stepx) / 2) / p->raydirx;
	else
		p->walldist = (p->mapy - p->dper_y + (1 - p->stepy) / 2) / p->raydiry;
	p->lineheight = (p->win_y / p->walldist);
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
		}
		// on check si le rayon a touché un mur de la map
		if (p->map[p->mapx][p->mapy] > '0')
			p->hit = 1;
	}
	calculate_wall_dist(p);
}

void	init_var1(t_parse *p)
{
	p->camx = 2 * p->raycastx / (double)p->win_x - 1;
	p->raydirx = p->dirx + p->planex * p->camx;
	p->raydiry = p->diry + p->planey * p->camx;
	p->mapx = (int)(p->dper_x / minimap);
	p->mapy = (int)(p->dper_y / minimap);
	p->deltadistx = sqrt(1 + (p->raydiry * p->raydiry) / (p->raydirx * p->raydirx));
	p->deltadisty =  sqrt(1 + (p->raydirx * p->raydirx) / (p->raydiry * p->raydiry));
	p->hit = 0;
}

void	raycasting_main(t_parse *p)
{
	p->raycastx = 0;
	p->dper_x = (double)(p->per_x / minimap);
	p->dper_y = (double)(p->per_y / minimap);
	while (p->raycastx < p->win_x)
	{
		init_var1(p);
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
