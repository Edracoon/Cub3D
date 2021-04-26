/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 17:03:22 by epfennig          #+#    #+#             */
/*   Updated: 2021/04/26 16:06:17 by epfennig         ###   ########.fr       */
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
	int y = p->win_y - 1;

	while (y > p->drawend)
	{
		my_mlx_pixel_put(p, p->raycastx, y--, p->floor_color);
	}
}

unsigned int	get_color_textu(t_parse *p, int x, int y, int nb)
{
	char	*dst;

	dst = p->textu[nb].addr + (y * p->textu[nb].line_length + x * (p->textu[nb].bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	init_dir_textu(t_parse *p)
{
	if (p->side == 0 && p->raydirx < 0)
		p->textdir = 0;
	if (p->side == 0 && p->raydirx >= 0)
		p->textdir = 1;
	if (p->side == 1 && p->raydiry < 0)
		p->textdir = 2;
	if (p->side == 1 && p->raydiry >= 0)
		p->textdir = 3;
}

void	draw_line(t_parse *p)
{
	int				y;
	double			wallx;
	int				texx;
	int				texy;
	double			texpos;
	double			step;
	unsigned int	color;

	init_dir_textu(p);
	y = p->drawstart;
	if (p->side == 0)
		wallx = p->dper_y + p->walldist * p->raydiry;
	else
		wallx = p->dper_x + p->walldist * p->raydirx;
	wallx -= floor((wallx));
	texx = (int)(wallx * (double)(64));
	if (p->side == 0 && p->raydirx > 0)
		texx = 64 - texx - 1;
	if (p->side == 1 && p->raydiry < 0)
		texx = 64 - texx -1;
	step = 1.0 * 64 / p->lineheight;
	texpos = (p->drawstart - p->win_y / 2 + p->lineheight / 2) * step;
	while (y <= p->drawend)
	{
		texy = (int)texpos & (64 - 1);
		texpos += step;
		color = get_color_textu(p, texx, texy, p->textdir);
		if (p->side == 1)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(p, p->raycastx, y, color);
		y++;
	}
}

void	calculate_wall_dist(t_parse *p)
{
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
		p->deltadistx = sqrt(1 + (p->raydiry * p->raydiry) / (p->raydirx * p->raydirx));
	if (p->raydirx == 0)
		p->deltadisty = 0;
	else if (p->raydirx == 1)
		p->deltadisty = 1;
	else
		p->deltadisty =  sqrt(1 + (p->raydirx * p->raydirx) / (p->raydiry * p->raydiry));
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
	sprite_casting(p);
}
