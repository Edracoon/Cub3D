/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data_utils_two.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:13:16 by marvin            #+#    #+#             */
/*   Updated: 2021/04/29 18:52:02 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "cub3d.h"
#include "libft/libft.h"

int	sprite_text_parse(char *line, t_parse *parse)
{
	char	**split;

	parse->s += 1;
	if (parse->s > 1)
		ft_error("Error\nMore than one sprite texture", parse);
	split = ft_split(line, ' ');
	if (!split[1])
		return (0);
	parse->sprite_text = split[1];
	free(split[0]);
	free(split);
	if (ft_strlen(parse->sprite_text) > 0)
		return (1);
	return (0);
}

void	atoi_rgb_floor(t_parse *parse, char *split0, char *split1, char *split2)
{
	if (!split0 || !split1 || !split2)
		ft_error("Error\nmalloc error\n", parse);
	parse->floor_r = ft_atoi(split0);
	parse->floor_g = ft_atoi(split1);
	parse->floor_b = ft_atoi(split2);
}

int	floor_color_parse(char *line, t_parse *parse)
{
	char	**split;
	char	**split2;

	parse->f += 1;
	if (parse->f > 1)
		ft_error("Error\nmore than one floor rgb\n", parse);
	split2 = ft_split(line, ' ');
	if (split2[1] && split2[2])
		ft_error("Error\nFloor color split error\n", parse);
	free(split2[0]);
	split = ft_split(split2[1], ',');
	if (!(is_num_boucle(split[0])) || (!(is_num_boucle(split[1]))
			|| (!(is_num_boucle(split[2])))))
	{
		free(split);
		free(split2[1]);
		ft_error("Error\nFloor color not numeric\n", parse);
	}
	atoi_rgb_floor(parse, split[0], split[1], split[2]);
	free(split[0]);
	free(split[1]);
	free(split[2]);
	free(split);
	parse->floor_color
		= (parse->floor_r << 16) | (parse->floor_g << 8) | (parse->floor_b);
	return (1);
}

int	ceiling_color_parse(char *line, t_parse *parse)
{
	char	**split;
	char	**split2;

	parse->c += 1;
	if (parse->c > 1)
		ft_error("Error\nMore than one ceiling rgb\n", parse);
	split2 = ft_split(line, ' ');
	free(split2[0]);
	split = ft_split(split2[1], ',');
	free(split2[1]);
	if (!split[0] || !split[1] || !split[2])
		ft_error("Error\nCeiling color split error\n", parse);
	parse->ceil_r = ft_atoi(split[0]);
	parse->ceil_g = ft_atoi(split[1]);
	parse->ceil_b = ft_atoi(split[2]);
	free(split[0]);
	free(split[1]);
	free(split[2]);
	free(split);
	parse->ceil_color
		= (parse->ceil_r << 16) | (parse->ceil_g << 8) | (parse->ceil_b);
	return (1);
}
