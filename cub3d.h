/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 11:52:22 by epfennig          #+#    #+#             */
/*   Updated: 2021/03/11 18:11:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_data
{
	int		rendu_x;
	int		rendu_y;
	char	*north_text;
	char	*south_text;
	char	*west_text;
	char	*east_text;
	char	*sprite_text;
	int		floor_color_r;
	int		floor_color_g;
	int		floor_color_b;
	int		ceiling_color_r;
	int		ceiling_color_g;
	int		ceiling_color_b;
	int		arg_save;
}	t_data;

void	get_map_data(char *cub, t_data *data);
int		main(int ac, char *av[]);
int		resolution_data(char *line, t_data *data);
int		north_text_data(char *line, t_data *data);
int		east_text_data(char *line, t_data *data);
int		west_text_data(char *line, t_data *data);
int		south_text_data(char *line, t_data *data);

#endif
