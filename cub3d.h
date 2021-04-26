/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 11:52:22 by epfennig          #+#    #+#             */
/*   Updated: 2021/04/26 12:13:06 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# define rotspeed 0.07

typedef struct s_sprite
{
	double x;
	double y;
}	t_sprite;

typedef struct s_spr
{
	double		x;
	double		y;
	double		spritex;
	double		spritey;
	int			texture;
	double		*zbuffer;
	int			*spriteord;
	double		*spritedist;
	int			nbspr;
	double		invdet;
	double		transformx;
	double		transformy;
	int			spritescreenx;
	int			spriteheight;
	int			spritewidht;
	int			drawstarty;
	int			drawendy;
	int			drawstartx;
	int			drawendx;
}	t_spr;

typedef struct s_textu
{
	void		*mlx_win;
	void		*mlx;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}	t_textu;

typedef struct s_parse
{
	char		map[255][255];
	int			win_x;
	int			win_y;
	int			minimap;
	double		speed;

	int			per_x;
	int			per_y;
	double		dper_x; // pos x du perso avec un double pour les decimaux
	double		dper_y; // pos y du perso avec un double pour les decimaux
	int			kill_win;
	int			forward;
	int			backward;
	int			leftward;
	int			rightward;
	int			rot_left;
	int			rot_right;
	int			mine;

	int			raycastx;
	double		dirx; // position x du vecteur de direction  |
	double		diry; // position y du vecteur de direction  |--> ce qui fait la direction initiale du vecteur
	double		planex; // 2D raycaster version de la camera plane
	double		planey;
	double		curfram;
	double		oldfram;
	double		camx;
	double		raydirx;
	double		raydiry;
	int			mapx; // pos X du carré de la map ou le rayon actuel se trouve
	int			mapy; // pos y du carré de la map ou le rayon actuel se trouve
	double		sidedistx; // la distance que le rayon a à parcourir de sa position de depart jusqu'au premier x-side
	double		sidedisty; // la distance que le rayon a à parcourir de sa position de depart jusqu'au premier y-side
	double		deltadistx; // la distance que le rayon a à parcourir depuis un x-side jusqu'au x-side suivant
	double		deltadisty; // la distance que le rayon a à parcourir depuis un y-side jusqu'au y-side suivant
	double		walldist; // distance du mur / longueur du rayon
	int			stepx; // soit 1 soit - 1 en fonction de la direction du rayon (-x ou +x)
	int			stepy; // soit 1 soit - 1 en fonction de la direction du rayon (-x ou +x)
	int			hit; // un mur a etait touché ? peut on finir la boucle ?
	int			side; // si un x-side ou un y-side d'un carré est touché. si x, side = 0, si y, side = 1,
	int			lineheight; // hauteur de la ligne qu'on va dessiner (ligne d'un pixel du mur)
	int			drawstart; // pos y du haut de la colone du mur qu'on va dessiner
	int			drawend; // pos y du bas de la colone du mur qu'on va dessiner

	char		*north_text;
	char		*south_text;
	char		*west_text;
	char		*east_text;
	char		*sprite_text;
	int			imgsiz;
	t_textu		textu[7];
	int			textdir;

	int			floor_r;
	int			floor_g;
	int			floor_b;
	int			floor_color;

	char		dir;

	int			ceil_r;
	int			ceil_g;
	int			ceil_b;
	int			ceil_color;

	int			arg_save;

	void		*mlx_win;
	void		*mlx;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;

	t_spr		spr;
	t_sprite	*sprite;
}	t_parse;

int				main(int ac, char *av[]);
void			get_map_parse(char *cub, t_parse *parse);
int				resolution_parse(char *line, t_parse *parse);
int				north_text_parse(char *line, t_parse *parse);
int				east_text_parse(char *line, t_parse *parse);
int				west_text_parse(char *line, t_parse *parse);
int				south_text_parse(char *line, t_parse *parse);
int				sprite_text_parse(char *line, t_parse *parse);
int				floor_color_parse(char *line, t_parse *parse);
int				ceiling_color_parse(char *line, t_parse *parse);
unsigned int	get_color_textu(t_parse *p, int x, int y, int nb);
void			raycasting_main(t_parse *p);
void			sprite_casting(t_parse *p);
int				mlx_main(t_parse *parse);
void			my_mlx_pixel_put(t_parse *data, int x, int y, int color);
int				parse_map(t_parse *p);
int				ft_mouvement(t_parse *p);
unsigned int	get_color_textu(t_parse *p, int x, int y, int nb);

int				key_pressed(int keycode, t_parse *p);
int				key_released(int keycode, t_parse *p);

#endif
