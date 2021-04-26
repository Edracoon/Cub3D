/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage_mlx_draw.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 13:08:40 by epfennig          #+#    #+#             */
/*   Updated: 2021/04/26 12:24:02 by epfennig         ###   ########.fr       */
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
	double	temp;

	if (p->kill_win)
	{
		mlx_destroy_window(p->mlx, p->mlx_win);
		exit(0);
	}
	if (p->forward)
	{
		p->dper_x += p->dirx * p->speed;
		p->dper_y += p->diry * p->speed;
		if (p->map[((int)floor(p->dper_y))][((int)floor((p->dper_x + p->dirx * p->speed)))] == '1')
			p->dper_x -= p->dirx * p->speed;
		if (p->map[((int)floor((p->dper_y + p->diry * p->speed)))][((int)floor(p->dper_x))] == '1')
			p->dper_y -= p->diry * p->speed;
	}
	if (p->backward)
	{
		p->dper_x -= p->dirx * p->speed;
		p->dper_y -= p->diry * p->speed;
		if (p->map[((int)floor(p->dper_y))][((int)floor((p->dper_x - p->dirx * p->speed)))] == '1')
			p->dper_x += p->dirx * p->speed;
		if (p->map[((int)floor((p->dper_y - p->diry * p->speed)))][((int)floor(p->dper_x))] == '1')
			p->dper_y += p->diry * p->speed;
	}
	if (p->rightward)
	{
		if (p->map[(int)(floor(p->dper_y))][(int)(floor((p->dper_x - p->diry * p->speed)))] == '0')
			p->dper_x -= p->diry * p->speed / 2;
		if (p->map[(int)(floor((p->dper_y + p->dirx * p->speed)))][(int)(floor(p->dper_x))] == '0')
			p->dper_y += p->dirx * p->speed / 2;
	}
	if (p->leftward)
	{
		if (p->map[(int)floor(p->dper_y)][(int)floor((p->dper_x + p->diry * p->speed))] == '0')
			p->dper_x += p->diry * p->speed / 2;
		if (p->map[(int)floor((p->dper_y - p->dirx * p->speed))][(int)floor(p->dper_x)] == '0')
			p->dper_y -= p->dirx * p->speed / 2;
	}
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
	max_y = y + (p->minimap) + p->speed - 1;
	max_x = x + (p->minimap) + p->speed - 1;
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
	max_y = y + p->minimap;
	max_x = x + p->minimap;
	while (x < max_x)
	{
		y = temp;
		while (y < max_y)
		{
			my_mlx_pixel_put(p, x, y, couleur);
			if (y % (p->minimap) == 0)
				my_mlx_pixel_put(p, x, y, 0x00000000);
			if (x % (p->minimap) == 0)
				my_mlx_pixel_put(p, x, y, 0x00000000);
			y++;
		}
		x++;
	}
}

void	affiche_minimap(t_parse *p)
{
	int	x;
	int	y;
	int	i;
	int	j;

	i = -1;
	j = 0;
	x = 0;
	y = 0;
	while (p->map[++i][j])
	{
		x = 0;
		while (p->map[i][j])
		{
			if (p->map[i][j] == '1')
				affiche_cube(p, x, y, 0x00117864);
			if (p->map[i][j] == '0')
				affiche_cube(p, x, y, 0x0048c9b0);
			if (p->map[i][j] == '2')
				affiche_cube(p,x ,y, 0x00e18080);
			affiche_perso(p, p->dper_x * p->minimap, p->dper_y * p->minimap + 1, 0x00ebfe00);
			x += p->minimap;
			j++;
		}
		j = 0;
		y += p->minimap;
	}
}

int	ft_affiche_image(t_parse *p)
{
	raycasting_main(p);
	sprite_casting(p);
	affiche_minimap(p);
	ft_mouvement(p);
	mlx_put_image_to_window(p->mlx, p->mlx_win, p->img, 0, 0);
	return (0);
}

void	ft_init_dir(t_parse *p)
{
	if (p->dir == 'N')
	{
		p->diry = -1;
		p->planex = 0.66;
	}
	if (p->dir == 'S')
	{
		p->diry = 1;
		p->planex = -0.66;
	}
	if (p->dir == 'W')
	{
		p->dirx = -1;
		p->planey = -0.66;
	}
	if (p->dir == 'E')
	{
		p->dirx = 1;
		p->planey = 0.66;
	}
}

void	ft_init1(t_parse *p)
{
	p->dper_x = (double)p->per_x / p->minimap;
	p->dper_y = (double)p->per_y / p->minimap;
	p->dirx = 0;
	p->diry =  0;
	p->planex = 0.000000000001;
	p->planey = 0.000000000001;
	p->speed = 0.05;
	ft_init_dir(p);
}

void	get_textu_addr(t_parse *p)
{
	int x;

	x = -1;
	while (++x <= 4)
		p->textu[x].addr = mlx_get_data_addr(p->textu[x].img, &p->textu[x].bits_per_pixel,
			&p->textu[x].line_length, &p->textu[x].endian);
}

int	get_textu_data(t_parse *p)
{
	p->imgsiz = 64;
	p->textu[0].img = mlx_xpm_file_to_image(p->mlx, p->south_text, &p->imgsiz, &p->imgsiz);
	p->textu[1].img = mlx_xpm_file_to_image(p->mlx, p->north_text, &p->imgsiz, &p->imgsiz);
	p->textu[2].img = mlx_xpm_file_to_image(p->mlx, p->west_text, &p->imgsiz, &p->imgsiz);
	p->textu[3].img = mlx_xpm_file_to_image(p->mlx, p->east_text, &p->imgsiz, &p->imgsiz);
	p->textu[4].img = mlx_xpm_file_to_image(p->mlx, p->sprite_text, &p->imgsiz, &p->imgsiz);
	if (p->textu[0].img == NULL || p->textu[1].img == NULL || p->textu[2].img == NULL ||
		p->textu[3].img == NULL || p->textu[4].img == NULL)
	{
		printf("Error\nTextures path error\n");
		return (-1);
	}
	get_textu_addr(p);
	return (0);
}

int	mlx_main(t_parse *p)
{
	ft_init1(p);

	p->mlx = mlx_init();
	p->mlx_win = mlx_new_window(p->mlx, p->win_x, p->win_y, "Cub3D");
	p->img = mlx_new_image(p->mlx, p->win_x, p->win_y);
	p->addr = mlx_get_data_addr(p->img, &p->bits_per_pixel,&p->line_length, &p->endian);
	if (get_textu_data(p) == -1)
		return (-1);
	mlx_hook(p->mlx_win, 2, 1L << 0, key_pressed, p);
	mlx_hook(p->mlx_win, 3, 1L << 1, key_released, p);
	mlx_loop_hook(p->mlx, ft_affiche_image, p);
	mlx_loop(p->mlx);
	//free(p);
	return (0);
}
