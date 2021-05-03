/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:48:47 by epfennig          #+#    #+#             */
/*   Updated: 2021/05/03 11:29:59 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line/get_next_line.h"
#include "../includes/cub3d.h"
#include "../libft/libft.h"

int	key_pressed(int keycode, t_parse *p)
{
	if (keycode == 49)
		p->speed = 0.1;
	if (keycode == 53)
		p->kill_win = 1;
	if (keycode == 13)
		p->forward = 1;
	if (keycode == 1)
		p->backward = 1;
	if (keycode == 2)
		p->rightward = 1;
	if (keycode == 0)
		p->leftward = 1;
	if (keycode == 123)
		p->rot_left = 1;
	if (keycode == 124)
		p->rot_right = 1;
	return (0);
}

int	key_released(int keycode, t_parse *p)
{
	if (keycode == 49)
		p->speed = 0.05;
	if (keycode == 53)
		p->kill_win = 0;
	if (keycode == 13)
		p->forward = 0;
	if (keycode == 1)
		p->backward = 0;
	if (keycode == 2)
		p->rightward = 0;
	if (keycode == 0)
		p->leftward = 0;
	if (keycode == 123)
		p->rot_left = 0;
	if (keycode == 124)
		p->rot_right = 0;
	return (0);
}
