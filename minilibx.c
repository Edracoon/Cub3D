/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 13:08:40 by epfennig          #+#    #+#             */
/*   Updated: 2021/03/24 17:46:54 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "cub3d.h"
#include "libft/libft.h"

void	my_mlx_pixel_put(t_parse *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	ft_mouvement(t_parse *p)
{
	int	x_max;
	int	y_max;

	x_max = p->per_x + (minimap / 2);
	y_max = p->per_y + (minimap / 2);
	printf("x = %i | y = %i\n", p->per_x, p->per_y);
	if (p->kill_win)
	{
		mlx_destroy_window(p->mlx, p->mlx_win);
		exit(0);
	}
	if (p->forward)
	{
		p->per_y += -speed;
		if (p->map[p->per_y / minimap][p->per_x / minimap] == '1'
			|| p->map[p->per_y / minimap][(x_max) / minimap] == '1')
			p->per_y += speed;
	}
	if (p->backward)
	{
		p->per_y += speed;
		if (p->map[(y_max + speed) / minimap][p->per_x / minimap] == '1'
			|| p->map[(y_max + speed) / minimap][(x_max) / minimap] == '1')
			p->per_y += -speed;
	}
	if (p->rightward)
	{
		p->per_x += speed;
		if (p->map[p->per_y / minimap][(x_max + speed) / minimap] == '1'
			|| p->map[y_max / minimap][(x_max + speed) / minimap] == '1')
			p->per_x += -speed;
	}
	if (p->leftward)
	{
		p->per_x += -speed;
		if (p->map[p->per_y / minimap][p->per_x / minimap] == '1'
			|| p->map[(y_max) / minimap][p->per_x / minimap] == '1')
			p->per_x += speed;
	}
	return (1);
}

void	affiche_perso(t_parse *p, int x, int y, int couleur)
{
	int	max_y;
	int	max_x;
	int	temp;

	temp = y;
	max_y = y + (minimap / 2) + speed - 1;
	max_x = x + (minimap / 2) + speed - 1;
	while (x < max_x)
	{
		y = temp;
		while (y < max_y)
			my_mlx_pixel_put(p, x, y++, couleur);
		x++;
	}
}

void	affiche_cube(t_parse *p, int x, int y, int couleur)
{
	int	max_y;
	int	max_x;
	int	temp;

	temp = y;
	max_y = y + minimap;
	max_x = x + minimap;
	while (x < max_x)
	{
		y = temp;
		while (y < max_y)
		{
			my_mlx_pixel_put(p, x, y, couleur);
			if (y % (minimap) == 0)
				my_mlx_pixel_put(p, x, y, 0x00000000);
			if (x % (minimap) == 0)
				my_mlx_pixel_put(p, x, y, 0x00000000);
			y++;
		}
		x++;
	}
}
/*
void	ray_print(int x, int y, t_parse *p)
{
	while (x >= p->per_x && y >= p->per_y)
	{
		my_mlx_pixel_put(p, x + 3.5, y + 3.5, 0x00fc0000);
		x--;
		y--;
	}
}

void	affiche_ray(t_parse *p)
{
	int	x;
	int y;

	x = p->per_x + 50;
	y = p->per_y + 50;
	ray_print(x, y, p);
}
*/

void	affiche_hud(t_parse *p)
{
	int y = p->win_y - 64;
	int x = p->win_x / 3;
	int c = 0;

	while (x < p->win_x)
	{
		while (c <= 6)
		{
			my_mlx_pixel_put(p, x, y, 0x00a09c9c);
			y++;
			c++;
		}
		x += 64;
		my_mlx_pixel_put(p, x, y, 0x00a09c9c);
	}
}

int	ft_affiche_image(t_parse *p)
{
	int		x;
	int 	y;
	int		i;
	int		j;

	i = 0;
	j = 0;
	x = 0;
	y = 0;
	ft_mouvement(p);
	while (p->map[i][j])
	{
		x = 0;
		while (p->map[i][j])
		{
			if (p->map[i][j] == '1')
				affiche_cube(p, x, y, p->ceil_color);
			if (p->map[i][j] == '0')
				affiche_cube(p, x, y, p->floor_color);
			affiche_perso(p, p->per_x + 1, p->per_y + 1, 0x00ebfe00);
			//affiche_ray(p);
			j++;
			x += minimap;
		}
		j = 0;
		y += minimap;
		i++;
	}
	raycasting_main(p);
	affiche_hud(p);
	mlx_put_image_to_window(p->mlx, p->mlx_win, p->img, 0, 0);
	return (0);
}

int	mlx_main(t_parse *p)
{
	p->mlx = mlx_init();
	p->mlx_win = mlx_new_window(p->mlx, p->win_x, p->win_y, "Cub3D");
	p->img = mlx_new_image(p->mlx, p->win_x, p->win_y);
	p->addr = mlx_get_data_addr(p->img, &p->bits_per_pixel,&p->line_length, &p->endian);
	mlx_hook(p->mlx_win, 2, 1L << 0, key_pressed, p);
	mlx_hook(p->mlx_win, 3, 1L << 1, key_released, p);
	mlx_loop_hook(p->mlx, ft_affiche_image, p);
	mlx_loop(p->mlx);
	free(p);
	return (0);
}
