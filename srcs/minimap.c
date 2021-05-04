/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 11:17:17 by epfennig          #+#    #+#             */
/*   Updated: 2021/05/04 16:09:31 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line/get_next_line.h"
#include "../includes/cub3d.h"
#include "../libft/libft.h"

void	my_mlx_pixel_put(t_parse *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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
	int		max_y;
	int		max_x;
	int		temp;

	temp = y;
	max_y = y + p->minimap;
	max_x = x + p->minimap;
	while (x < max_x)
	{
		y = temp;
		while (y < max_y)
		{
			my_mlx_pixel_put(p, x, y, couleur);
			y++;
		}
		x++;
	}
}

void	affiche_minimap(t_parse *p, int x, int y, int i)
{
	int	j;

	j = 0;
	while (p->sizecollum > i && p->map[i][j])
	{
		x = 0;
		while (p->sizeline > j && p->map[i][j])
		{
			if (p->map[i][j] == '1')
				affiche_cube(p, x, y, 0x00117864);
			if (p->map[i][j] == '0')
				affiche_cube(p, x, y, 0x0048c9b0);
			if (p->map[i][j] == '2')
				affiche_cube(p, x, y, 0x00ff0000);
			affiche_perso(p, p->dper_x * p->minimap, \
				p->dper_y * p->minimap + 1, 0x00ebfe00);
			x += p->minimap;
			j++;
		}
		i++;
		j = 0;
		y += p->minimap;
	}
}
