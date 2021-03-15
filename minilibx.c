/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 13:08:40 by epfennig          #+#    #+#             */
/*   Updated: 2021/03/15 16:42:48 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "cub3d.h"
#include "libft/libft.h"

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

//nt	key_hook(int keycode, void *key)

void	affiche_cube(t_data img, int x, int y, int couleur)
{
	int max_y;
	int max_x;
	int temp;

	temp = y;
	max_y = y + 30;
	max_x = x + 30;
	while (x < max_x)
	{
		y = temp;
		while (y < max_y)
			my_mlx_pixel_put(&img, x, y++, couleur);
		x++;
	}
}

int     mlx_main(t_parse *parse)
{
	int	x;
	int y;
	int	i;
	int	j;
	void	*mlx_win;
	void    *mlx;
	t_data	img;

	i = 0;
	j = 0;
	x = 100;
	y = 100;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, parse->win_x, parse->win_y, "Cub3D");
	img.img = mlx_new_image(mlx, parse->win_x, parse->win_y);

	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
		&img.endian);
//	affiche_mur(img, 0, 0);
//	affiche_vide(img, 0, 50);
	while (parse->map[i][j])
	{
		x = 200;
		while (parse->map[i][j])
		{
			if (parse->map[i][j] == '1')
				affiche_cube(img, x, y, parse->ceil_color);
			if (parse->map[i][j] == '0')
				affiche_cube(img, x, y, parse->floor_color);
			if (parse->map[i][j] == 'W' || parse->map[i][j] == 'S'
				|| parse->map[i][j] == 'E' || parse->map[i][j] == 'N')
				affiche_cube(img, x, y, 0x00ebfe00);
			j++;
			x += 30;
		}
		j = 0;
		y += 30;
		i++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	//mlx_key_hook(mlx_win, key_hook);
	mlx_loop(mlx);
	return (0);
}
