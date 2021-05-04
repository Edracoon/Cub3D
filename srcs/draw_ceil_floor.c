/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceil_floor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:13:58 by epfennig          #+#    #+#             */
/*   Updated: 2021/05/04 11:36:52 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line/get_next_line.h"
#include "../includes/cub3d.h"
#include "../libft/libft.h"

void	draw_ceiling(t_parse *p)
{
	int	y;

	y = 0;
	while (y < p->drawstart)
	{
		my_mlx_pixel_put(p, p->raycastx, y++, p->ceil_color);
	}
}

void	draw_floor(t_parse *p)
{
	int	y;

	y = p->win_y - 1;
	while (y > p->drawend)
	{
		my_mlx_pixel_put(p, p->raycastx, y--, p->floor_color);
	}
}

unsigned int	get_color_textu(t_parse *p, int x, int y, int nb)
{
	char	*dst;

	dst = p->textu[nb].addr + (y * p->textu[nb].line_length +\
		x * (p->textu[nb].bits_per_pixel / 8));
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
