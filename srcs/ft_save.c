/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 11:32:45 by epfennig          #+#    #+#             */
/*   Updated: 2021/05/04 14:36:07 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line/get_next_line.h"
#include "../includes/cub3d.h"
#include "../libft/libft.h"

void	entete_bmp(t_parse *p, int fd)
{
	int	size;

	size = (p->win_x * p->win_y) * 4 + 54;
	write(fd, "BM", 2);
	write(fd, &size, 4);
	size = 0;
	write(fd, &size, 2);
	write(fd, &size, 2);
	size = 54;
	write(fd, &size, 4);
	size = 40;
	write(fd, &size, 4);
	write(fd, &p->win_x, 4);
	write(fd, &p->win_y, 4);
	size = 1;
	write(fd, &size, 2);
	write(fd, &p->bits_per_pixel, 2);
	size = 0;
	write(fd, &size, 4);
	write(fd, &size, 4);
	write(fd, &size, 4);
	write(fd, &size, 4);
	write(fd, &size, 4);
	write(fd, &size, 4);
}

void	ft_save(t_parse *p)
{
	int	x;
	int	y;
	int	fd;

	x = 0;
	y = p->win_y;
	fd = open("./image.bmp", O_CREAT | O_RDWR);
	entete_bmp(p, fd);
	while (y > 0)
	{
		x = 0;
		while (x < p->win_x)
		{
			write(fd, &p->addr[y * p->line_length + x * 4], 4);
			x++;
		}
		y--;
	}
	system("chmod 777 image.bmp");
	ft_error("Screen Shot\n", p);
}
