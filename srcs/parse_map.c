/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 11:48:08 by epfennig          #+#    #+#             */
/*   Updated: 2021/05/05 12:50:56 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line/get_next_line.h"
#include "../includes/cub3d.h"
#include "../libft/libft.h"

void	ft_setup_dir(t_parse *p, int i, int j)
{
	p->dir = p->map[i][j];
	p->map[i][j] = '0';
	p->dper_x = j + 0.5;
	p->dper_y = i + 0.5;
}

int	find_player(t_parse *p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	p->spr.nbspr = 0;
	while (p->sizecollum > i && p->map[i][j])
	{
		while (p->map[i][j] && p->sizeline > j)
		{
			if (p->map[i][j] == 'W' || p->map[i][j] == 'E'
				|| p->map[i][j] == 'N' || p->map[i][j] == 'S')
				ft_setup_dir(p, i, j);
			if (p->map[i][j] == '2')
				p->spr.nbspr += 1;
			j++;
		}
		i++;
		j = 0;
	}
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
	while (p->sizecollum > i && p->map[i][j])
	{
		while (p->map[i][j] && p->sizeline > j)
		{
			if (p->map[i][j] == '2' && nb < p->spr.nbspr)
			{
				p->sprite[nb].x = (double)j + 0.5;
				p->sprite[nb].y = (double)i + 0.5;
				nb++;
			}
			j++;
		}
		i++;
		j = 0;
	}
}

void	init_sprite(t_parse *p)
{
	p->spr.spriteord = (int *)malloc(sizeof(int) * p->spr.nbspr);
	p->spr.spritedist = (double *)malloc(sizeof(double) * p->spr.nbspr);
	if (!(p->spr.spriteord) || !(p->spr.spritedist))
		exit(0);
	p->spr.zbuffer = (double *)malloc(sizeof(double) * p->win_x);
	if (!(p->spr.zbuffer))
		exit(0);
	p->sprite = (t_sprite *)malloc(sizeof(t_sprite) * p->spr.nbspr);
	if (!p->sprite)
		exit(0);
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

int	parse_map(t_parse *p)
{
	check_map_valid(p);
	if (p->win_x > 1920)
		p->win_x = 1920;
	if (p->win_y > 1080)
		p->win_y = 1080;
	if (p->win_x < 320)
		p->win_x = 320;
	if (p->win_y < 200)
		p->win_y = 200;
	p->minimap = (p->win_x / 3) / p->sizeline;
	find_player(p);
	init_sprite(p);
	sprite_handler(p);
	return (1);
}
