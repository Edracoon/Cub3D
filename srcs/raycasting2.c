/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:11:17 by epfennig          #+#    #+#             */
/*   Updated: 2021/05/05 13:52:32 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line/get_next_line.h"
#include "../includes/cub3d.h"
#include "../libft/libft.h"

void	draw_line2(t_parse *p)
{
	unsigned int	color;

	while (p->ty <= p->drawend)
	{
		p->texy = (int)p->texpos & (64 - 1);
		p->texpos += p->step;
		color = get_color_textu(p, p->texx, p->texy, p->textdir);
		if (p->side == 1)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(p, p->raycastx, p->ty, color);
		p->ty++;
	}
}

void	draw_line(t_parse *p)
{
	init_dir_textu(p);
	p->ty = p->drawstart;
	if (p->side == 0)
		p->wallx = p->dper_y + p->walldist * p->raydiry;
	else
		p->wallx = p->dper_x + p->walldist * p->raydirx;
	p->wallx -= floor((p->wallx));
	p->texx = (int)(p->wallx * (double)(64));
	p->step = 64.0 / p->lineheight;
	p->texpos = (p->drawstart + p->lineheight / 2 - p->win_y / 2) * p->step;
	draw_line2(p);
}

void	calculate_wall_dist(t_parse *p)
{
	if (p->side == 0)
		p->walldist = ((double)p->mapx - p->dper_x + \
			(1 - (double)p->stepx) / 2) / p->raydirx;
	else
		p->walldist = ((double)p->mapy - p->dper_y + \
			(1 - (double)p->stepy) / 2) / p->raydiry;
	p->lineheight = ((double)p->win_y * p->ratio) / (p->walldist);
	p->drawstart = -p->lineheight / 2 + p->win_y / 2;
	if (p->drawstart < 0)
		p->drawstart = 0;
	p->drawend = p->lineheight / 2 + p->win_y / 2;
	if (p->drawend >= p->win_y)
		p->drawend = p->win_y - 1;
}
