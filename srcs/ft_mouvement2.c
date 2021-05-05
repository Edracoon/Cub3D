/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouvement2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:15:56 by epfennig          #+#    #+#             */
/*   Updated: 2021/05/05 11:37:48 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line/get_next_line.h"
#include "../includes/cub3d.h"
#include "../libft/libft.h"

int	ft_destroy_windows(t_parse *p)
{
	mlx_destroy_window(p->mlx, p->mlx_win);
	if (p->sprite)
		free(p->sprite);
	if (p->spr.spriteord)
		free(p->spr.spriteord);
	if (p->spr.spritedist)
		free(p->spr.spritedist);
	if (p->spr.zbuffer)
		free(p->spr.zbuffer);
	if (p)
		free(p);
	exit(1);
	return (1);
}

void	ft_forward(t_parse *p)
{
	if (p->map[((int)floor(p->dper_y))][((int)(\
		floor((p->dper_x + p->dirx * p->speed))))] == '0')
		p->dper_x += p->dirx * p->speed;
	if (p->map[((int)floor((p->dper_y + p->diry * p->speed)))][((int)(\
		floor(p->dper_x)))] == '0')
		p->dper_y += p->diry * p->speed;
}

void	ft_backward(t_parse *p)
{
	if (p->map[((int)floor(p->dper_y))][((int)floor(\
		(p->dper_x - p->dirx * p->speed)))] == '0')
		p->dper_x -= p->dirx * p->speed;
	if (p->map[((int)floor((p->dper_y - p->diry * p->speed)))][(\
		(int)floor(p->dper_x))] == '0')
		p->dper_y -= p->diry * p->speed;
}

int	ft_mouvement(t_parse *p)
{
	if (p->kill_win)
		ft_destroy_windows(p);
	if (p->forward)
		ft_forward(p);
	if (p->backward)
		ft_backward(p);
	if (p->rightward)
		ft_rightward(p);
	if (p->leftward)
		ft_leftward(p);
	if (p->rot_right)
		ft_rotright(p);
	if (p->rot_left)
		ft_rotleft(p);
	return (1);
}
