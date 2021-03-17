/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 13:08:40 by epfennig          #+#    #+#             */
/*   Updated: 2021/03/17 16:58:55 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "cub3d.h"
#include "libft/libft.h"

void            my_mlx_pixel_put(t_parse *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int	ft_mouvement(t_parse *p)
{
	printf("x = %i | y = %i\n", p->per_x, p->per_y);
	if (p->kill_win)
		mlx_destroy_window(p->mlx, p->mlx_win);
	if (p->forward)
	{
		p->per_y += -8;
		if (p->map[p->per_y / 64][p->per_x / 64] == '1')
			p->per_y += 8;
	}
	if (p->backward)
	{
		p->per_y += 8;
		if (p->map[p->per_y / 64][p->per_x / 64] == '1')
			p->per_y += -8;
	}
	if (p->rightward)
	{
		p->per_x += 8;
		if (p->map[p->per_y / 64][p->per_x / 64] == '1')
			p->per_x += -8;
	}
	if (p->leftward)
	{
		p->per_x += -8;
		if (p->map[p->per_y / 64][p->per_x / 64] == '1')
			p->per_x += 8;
	}
	return (1);
}

void		affiche_perso(t_parse *p, int x, int y, int couleur)
{
	int max_y;
	int max_x;
	int temp;

	temp = y;
	max_y = y + 8;
	max_x = x + 8;
	while (x < max_x)
	{
		y = temp;
		while (y < max_y)
			my_mlx_pixel_put(p, x, y++, couleur);
		x++;
	}
}

void		affiche_cube(t_parse *p, int x, int y, int couleur)
{
	int max_y;
	int max_x;
	int temp;
	(void)couleur;

	temp = y;
	max_y = y + 64;
	max_x = x + 64;
	while (x < max_x)
	{
		y = temp;
		while (y < max_y)
		{
			my_mlx_pixel_put(p, x, y, couleur);
			if (y == max_y - 1)
				my_mlx_pixel_put(p, x, y, 000000);
			if (x == max_x - 1)
				my_mlx_pixel_put(p, x, y, 000000);
			y++;
		}
		x++;
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
			affiche_perso(p, p->per_x, p->per_y, 0x00ebfe00);
			j++;
			x += 64;
		}
		j = 0;
		y += 64;
		i++;
	}
	mlx_put_image_to_window(p->mlx, p->mlx_win, p->img, 0, 0);
	return (0);
}

int     mlx_main(t_parse *p)
{
	p->mlx = mlx_init();
	p->mlx_win = mlx_new_window(p->mlx, p->win_x, p->win_y, "Cub3D");
	p->img = mlx_new_image(p->mlx, p->win_x, p->win_y);
	p->addr = mlx_get_data_addr(p->img, &p->bits_per_pixel, &p->line_length, &p->endian);
	//mlx_key_hook(p->mlx_win, x_key_hook, p);
	//mlx_key_hook(p->mlx_win, y_key_hook, p);
	mlx_hook(p->mlx_win, 2, 1L<<0, key_pressed, p);
	mlx_hook(p->mlx_win, 3, 1L<<1, key_released, p);
	mlx_loop_hook(p->mlx, ft_affiche_image, p);
	mlx_loop(p->mlx);
	free(p);
	return (0);
}
