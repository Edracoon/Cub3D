/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 10:40:28 by epfennig          #+#    #+#             */
/*   Updated: 2021/03/23 17:36:08 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "cub3d.h"
#include "libft/libft.h"

void	raycasting_main(t_parse *p)
{
	int	x;
	int	w;

	x = 0;
	w = 64;
	p->dper_x = p->per_x;
	p->dper_y = p->per_y;
	while (x < w)
	{
		p->camx = 2 * x / w - 1;
		p->raydirx = p->dirx + p->planex * p->camx;
		p->raydiry = p->diry + p->planey * p->camx;
		p->mapx = (int)p->dper_x;
		p->mapy = (int)p->dper_y;
		p->deltadistx = fabs(1 / p->raydirx);
		p->deltadisty = fabs(1 / p->raydiry);
		p->hit = 0;
		x++;
	}
	printf("raydirx = %f | raydiry = %f camx = %f\n", p->raydirx, p->raydiry, p->camx);

}
