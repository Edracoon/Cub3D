/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:03:22 by epfennig          #+#    #+#             */
/*   Updated: 2021/05/05 14:48:36 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line/get_next_line.h"
#include "../includes/cub3d.h"
#include "../libft/libft.h"

void	ft_hit_wall(t_parse *p)
{
	while (p->hit == 0)
	{
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
		if (p->map[p->mapy][p->mapx] == '1')
			p->hit = 1;
	}
}

void	init_delta(t_parse *p)
{
	if (p->raydiry == 0)
		p->deltadistx = 0;
	else if (p->raydiry == 1)
		p->deltadistx = 1;
	else
		p->deltadistx = sqrt(1 + (p->raydiry * p->raydiry) \
			/ (p->raydirx * p->raydirx));
	if (p->raydirx == 0)
		p->deltadisty = 0;
	else if (p->raydirx == 1)
		p->deltadisty = 1;
	else
		p->deltadisty = sqrt(1 + (p->raydirx * p->raydirx) \
			/ (p->raydiry * p->raydiry));
}

void	ft_initstepxysidexy(t_parse *p)
{
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
		ft_initstepxysidexy(p);
		ft_hit_wall(p);
		calculate_wall_dist(p);
		draw_ceiling(p);
		draw_line(p);
		draw_floor(p);
		p->spr.zbuffer[p->raycastx] = p->walldist;
		p->raycastx++;
	}
}
