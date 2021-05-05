/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_init_draw.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 13:08:40 by epfennig          #+#    #+#             */
/*   Updated: 2021/05/05 11:37:07 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line/get_next_line.h"
#include "../includes/cub3d.h"
#include "../libft/libft.h"

int	ft_affiche_image(t_parse *p)
{
	raycasting_main(p);
	sprite_casting(p);
	affiche_minimap(p, 0, 0, 0);
	if (p->arg_save == 1)
		ft_save(p);
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
	p->ratio = ((double)p->win_x / (double)p->win_y) / (4.0 / 3.0);
	p->dirx = 0;
	p->diry = 0;
	p->planex = 0.000000000001;
	p->planey = 0.000000000001;
	p->speed = 0.08;
	ft_init_dir(p);
}

int	get_textu_data(t_parse *p)
{
	p->imgsiz = 64;
	p->textu[0].img = mlx_xpm_file_to_image(p->mlx, \
		p->south_text, &p->imgsiz, &p->imgsiz);
	p->textu[1].img = mlx_xpm_file_to_image(p->mlx, \
		p->north_text, &p->imgsiz, &p->imgsiz);
	p->textu[2].img = mlx_xpm_file_to_image(p->mlx, \
		p->west_text, &p->imgsiz, &p->imgsiz);
	p->textu[3].img = mlx_xpm_file_to_image(p->mlx, \
		p->east_text, &p->imgsiz, &p->imgsiz);
	p->textu[4].img = mlx_xpm_file_to_image(p->mlx, \
		p->sprite_text, &p->imgsiz, &p->imgsiz);
	if (p->textu[0].img == NULL || p->textu[1].img == NULL
		|| p->textu[2].img == NULL || p->textu[3].img == NULL
		|| p->textu[4].img == NULL)
		ft_error("Error\nTextures path error\n", p);
	get_textu_addr(p);
	return (0);
}

int	mlx_main(t_parse *p)
{
	ft_init1(p);
	p->mlx = mlx_init();
	p->mlx_win = mlx_new_window(p->mlx, p->win_x, p->win_y, "Cub3D");
	p->img = mlx_new_image(p->mlx, p->win_x, p->win_y);
	p->addr = mlx_get_data_addr(p->img, \
		&p->bits_per_pixel, &p->line_length, &p->endian);
	get_textu_data(p);
	mlx_hook(p->mlx_win, 2, 1L << 0, key_pressed, p);
	mlx_hook(p->mlx_win, 3, 1L << 1, key_released, p);
	mlx_hook(p->mlx_win, 17, 0, ft_destroy_windows, p);
	mlx_loop_hook(p->mlx, ft_affiche_image, p);
	mlx_loop(p->mlx);
	free(p);
	return (0);
}
