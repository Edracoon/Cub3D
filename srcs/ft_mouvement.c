/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouvement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:14:48 by epfennig          #+#    #+#             */
/*   Updated: 2021/05/05 13:13:47 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line/get_next_line.h"
#include "../includes/cub3d.h"
#include "../libft/libft.h"

void	ft_rightward(t_parse *p)
{
	if (p->map[(int)(floor(p->dper_y))][(int)(\
		floor((p->dper_x - p->diry * p->speed)))] == '0')
		p->dper_x -= p->diry * p->speed / 2;
	if (p->map[(int)(floor((p->dper_y + p->dirx * p->speed)))][(int)(\
		floor(p->dper_x))] == '0')
		p->dper_y += p->dirx * p->speed / 2;
}

void	ft_leftward(t_parse *p)
{
	if (p->map[(int)floor(p->dper_y)][(int)floor(\
		(p->dper_x + p->diry * p->speed))] == '0')
		p->dper_x += p->diry * p->speed / 2;
	if (p->map[(int)floor((p->dper_y - p->dirx * p->speed))][(int)(\
		floor(p->dper_x))] == '0')
		p->dper_y -= p->dirx * p->speed / 2;
}

void	ft_rotright(t_parse *p)
{
	double	temp;

	temp = p->dirx;
	p->dirx = p->dirx * cos(ROTSPEED / 2) - p->diry * sin(ROTSPEED / 2);
	p->diry = temp * sin(ROTSPEED / 2) + p->diry * cos(ROTSPEED / 2);
	temp = p->planex;
	p->planex = p->planex * cos(ROTSPEED / 2) - p->planey * sin(ROTSPEED / 2);
	p->planey = temp * sin(ROTSPEED / 2) + p->planey * cos(ROTSPEED / 2);
}

void	ft_rotleft(t_parse *p)
{
	double	temp;

	temp = p->dirx;
	p->dirx = p->dirx * cos(-ROTSPEED / 2) - p->diry * sin(-ROTSPEED / 2);
	p->diry = temp * sin(-ROTSPEED / 2) + p->diry * cos(-ROTSPEED / 2);
	temp = p->planex;
	p->planex = p->planex * cos(-ROTSPEED / 2) - p->planey * sin(-ROTSPEED / 2);
	p->planey = temp * sin(-ROTSPEED / 2) + p->planey * cos(-ROTSPEED / 2);
}
