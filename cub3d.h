/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 11:52:22 by epfennig          #+#    #+#             */
/*   Updated: 2021/03/10 13:38:15 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct	s_data
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
	int		arg_save;
}				t_data;

#endif
