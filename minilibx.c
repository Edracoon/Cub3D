/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 13:08:40 by epfennig          #+#    #+#             */
/*   Updated: 2021/03/30 17:33:02 by epfennig         ###   ########.fr       */
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
	int		x_max;
	int		y_max;
	double	temp;

	x_max = p->dper_x + (minimap / 2);
	y_max = p->dper_y + (minimap / 2);
	//p->dper_x = (double)p->per_x;
	//p->dper_x = (double)p->per_x;
	//printf("[x = %i | y = %i]  [dirx = %f | diry = %f] [planex = %f | planey = %f]\n", p->per_x, p->per_y, p->dirx, p->diry, p->planex, p->planey);
	if (p->kill_win)
	{
		mlx_destroy_window(p->mlx, p->mlx_win);
		exit(0);
	}
	if (p->forward)
	{
		if (p->map[((int)p->dper_y)][((int)(p->dper_x + p->dirx * speed))] == '0')
		{
			p->dper_x += p->dirx * speed;
		}
		if (p->map[((int)(p->dper_y + p->diry * speed))][((int)p->dper_x)] == '0')
		{
			p->dper_y += p->diry * speed;
		}
	}
	if (p->backward)
	{
		if (p->map[((int)p->dper_y)][((int)(p->dper_x + p->dirx * speed))] == '0')
		{
			p->dper_x -= p->dirx * speed;
		}
		if (p->map[((int)(p->dper_y + p->diry * speed))][((int)p->dper_x)] == '0')
		{
			p->dper_y -= p->diry * speed;
		}

	}
	//if (p->rightward)
	//{
	//}
	//if (p->leftward)
	//{
	//}
	if (p->rot_right)
	{
		temp = p->dirx;
		p->dirx = p->dirx * cos(rotspeed / 2) - p->diry * sin(rotspeed / 2);
		p->diry = temp * sin(rotspeed / 2) + p->diry * cos(rotspeed / 2);
		temp = p->planex;
		p->planex = p->planex * cos(rotspeed / 2) - p->planey * sin(rotspeed / 2);
		p->planey = temp * sin(rotspeed / 2) + p->planey * cos(rotspeed / 2);
	}
	if (p->rot_left)
	{
		temp = p->dirx;
		p->dirx = p->dirx * cos(-rotspeed / 2) - p->diry * sin(-rotspeed / 2);
		p->diry = temp * sin(-rotspeed / 2) + p->diry * cos(-rotspeed / 2);
		temp = p->planex;
		p->planex = p->planex * cos(-rotspeed / 2) - p->planey * sin(-rotspeed / 2);
		p->planey = temp * sin(-rotspeed / 2) + p->planey * cos(-rotspeed / 2);
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
	int	x;
	int	y;
	int	i;
	int	j;

	i = 0;
	j = 0;
	x = 0;
	y = 0;
	raycasting_main(p);
	while (p->map[i][j])
	{
		x = 0;
		while (p->map[i][j])
		{
			if (p->map[i][j] == '1')
				affiche_cube(p, x, y, p->ceil_color);
			if (p->map[i][j] == '0')
				affiche_cube(p, x, y, p->floor_color);
			affiche_perso(p, p->dper_x * minimap, p->dper_y * minimap + 1, 0x00ebfe00);
			//affiche_ray(p);
			j++;
			x += minimap;
		}
		j = 0;
		y += minimap;
		i++;
	}
	//affiche_hud(p);
	ft_mouvement(p);
	mlx_put_image_to_window(p->mlx, p->mlx_win, p->img, 0, 0);
	return (0);
}

void	ft_init_dir(t_parse *p)
{
	if (p->dir == 'N')
	{
		p->diry = -1;
		p->planey = -0.66;
	}
	if (p->dir == 'S')
	{
		p->diry = 1;
		p->planey = 0.66;
	}
	if (p->dir == 'W')
	{
		p->dirx = -1;
		p->planex = -0.66;
	}
	if (p->dir == 'E')
	{
		p->dirx = 1;
		p->planex = 0.66;
	}
}

void	ft_init1(t_parse *p)
{
	p->dper_x = (double)p->per_x / minimap;
	p->dper_y = (double)p->per_y / minimap;
	ft_init_dir(p);
}

int	mlx_main(t_parse *p)
{
	ft_init1(p);
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
