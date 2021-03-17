/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 11:52:22 by epfennig          #+#    #+#             */
/*   Updated: 2021/03/17 15:12:15 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13

typedef struct s_parse
{
	char		map[255][255];
	int			win_x;
	int			win_y;

	int			per_x;
	int			per_y;

	int			kill_win;
	int			forward;
	int			backward;
	int			leftward;
	int			rightward;

	char		*north_text;
	char		*south_text;
	char		*west_text;
	char		*east_text;
	char		*sprite_text;

	int			floor_r;
	int			floor_g;
	int			floor_b;
	int			floor_color;

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
}	t_parse;



int		main(int ac, char *av[]);

void	get_map_parse(char *cub, t_parse *parse);
int		resolution_parse(char *line, t_parse *parse);
int		north_text_parse(char *line, t_parse *parse);
int		east_text_parse(char *line, t_parse *parse);
int		west_text_parse(char *line, t_parse *parse);
int		south_text_parse(char *line, t_parse *parse);
int		sprite_text_parse(char *line, t_parse *parse);
int		floor_color_parse(char *line, t_parse *parse);
int		ceiling_color_parse(char *line, t_parse *parse);

int     mlx_main(t_parse *parse);
int		parse_map(t_parse *p);

int		key_pressed(int keycode, t_parse *p);
int		key_released(int keycode, t_parse *p);

#endif
