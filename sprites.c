/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:03:46 by epfennig          #+#    #+#             */
/*   Updated: 2021/04/22 15:14:52 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprite(t_parse *p)
{
	p->spr.spriteord = malloc(sizeof(int) * p->spr.nbspr);
	p->spr.spritedist = malloc(sizeof(int) * p->spr.nbspr);
	if (!(p->spr.spriteord) || !(p->spr.spritedist))
		exit(1);
}

void	sprite_handler(t_parse *p)
{
	int	i;
	int	j;
	int	nb;

	nb = 0;
	i = 0;
	j = 0;
	while (p->map[i][j])
	{
		j= 0;
	 	while (p->map[i][j])
	 	{
	 		if (p->map[i][j] == '2' && nb < p->spr.nbspr)
	 		{
				p->sprite[nb].x = j + 0.5;
				p->sprite[nb].y = i + 0.5;
	 			nb++;
	 		}
	 		j++;
	 	}
		i++;
	}
}

void	init_var_spr(t_parse *p)
{
	p->spr.spritex = 0;
	p->spr.spritey = 0;
	p->spr.texture = 0;
	p->spr.invdet = 0;
	p->spr.transformx = 0;
	p->spr.transformy = 0;
	p->spr.spritescreenx = 0;
	p->spr.spriteheight = 0;
	p->spr.spritewidht = 0;
	p->spr.drawstartx = 0;
	p->spr.drawstarty = 0;
	p->spr.drawendx = 0;
	p->spr.drawendy = 0;
}

void	sprite_casting(t_parse *p)
{
	int		i;
	//int		stripe;
	//int		texx;
	//int		texy;
	//int		y;
	//int		d;
	//int		color;
	int		j;
	double	tmp;

	init_sprite(p);
	init_var_spr(p);
	sprite_handler(p);
	// boucle qui trie les sprites par ordre d'appartition
	i = -1;
	while (++i < p->spr.nbspr)
	{
		p->spr.spriteord[i] = i;
		p->spr.spritedist[i] = ((p->dper_x - p->sprite[i].x)
				* (p->per_x - p->sprite[i].x) + (p->dper_y
					- p->sprite[i].y) * (p->dper_y - p->sprite[i].y));
		j = -1;
		while (++j < p->spr.nbspr - 1)
		{
			if (p->spr.spritedist[j] < p->spr.spritedist[j + 1])
			{
				tmp = p->spr.spritedist[j];
				p->spr.spritedist[j] = p->spr.spritedist[j + 1];
				p->spr.spritedist[j + 1] = tmp;
				tmp = p->spr.spriteord[j];
				p->spr.spriteord[j] = p->spr.spriteord[j + 1];
				p->spr.spriteord[j + 1] = (int)tmp;
			}
		}
	}
	i = -1;
	/*while (++i < p->spr.nbspr)
	{
		// calcul de la relativité de la postion du sprite par rapport a la position du joueur
		p->spr.spritex = p->sprite[p->spr.spriteord[i]].x - p->dper_x;
		p->spr.spritey = p->sprite[p->spr.spriteord[i]].y - p->dper_y;
		p->spr.invdet = 1.0 / (p->planex * p->diry - p->dirx * p->planey); // valeur demandée pour le calcul de la matrice inversée
		p->spr.transformx = p->spr.invdet * (p->diry * p->spr.spritex - p->dirx * p->spr.spritey);
		p->spr.transformy = p->spr.invdet * (-p->planey * p->spr.spritex + p->planex * p->spr.spritey);
		p->spr.spritescreenx = (int)((p->win_x / 2) * (1 + p->spr.transformx / p->spr.transformy));
		p->spr.spriteheight = abs((int)(p->win_y / p->spr.transformy));

//	Calcul lowest and highest pixel to fill in current stripe
		p->spr.drawstarty = -p->spr.spriteheight / 2 + p->win_y / 2;
		if (p->spr.drawstarty < 0)
			p->spr.drawstarty = 0;
		p->spr.drawendy = p->spr.spriteheight / 2 + p->win_y / 2;
		if (p->spr.drawendy >= p->win_y)
			p->spr.drawendy = p->win_y - 1;

//	Calcul width of the sprite
		p->spr.spritewidht = abs((int)(p->win_y / (p->spr.transformy)));
		p->spr.drawstartx = -p->spr.spritewidht / 2 + p->spr.spritescreenx;
		if (p->spr.drawstartx < 0)
			p->spr.drawstartx = 0;
		p->spr.drawendx = p->spr.spritewidht / 2 + p->spr.spritescreenx;
		if (p->spr.drawendx >= p->win_x)
			p->spr.drawendx = p->win_x - 1;

//	on regarde toutes les colonnes x du sprites a l'ecran pour les draw
		d = 0;
		y = p->spr.drawstarty;
		stripe = p->spr.drawstartx;
		while (stripe < p->spr.drawendx)
		{
			texx = (int)(256 * (stripe - (-p->spr.spritewidht / 2 + p->spr.spritescreenx)) * \
				64 / p->spr.spritewidht) / 256;
			if (p->spr.transformy > 0 && stripe > 0
				&& stripe < p->win_x && p->spr.transformy < p->spr.zbuffer[stripe])
			{
				while (y < p->spr.drawendy)
				{
					d = y * 256 - p->win_y * 128 + p->spr.spriteheight * 128;
					texy = ((d * 64) / p->spr.spriteheight) / 256;
					color = get_color_textu(p, texx, texy, 4);
					//mlx_put_image_to_window(p->mlx, p->mlx_win, p->textu[4].img, 0, 0);
					my_mlx_pixel_put(p, y, stripe, 0x00ff0000);
					y++;
				}
			}
			stripe++;
		}
	}*/
	free(p->spr.spriteord);
	free(p->spr.spritedist);
}

