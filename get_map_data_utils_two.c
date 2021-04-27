/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data_utils_two.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 18:13:16 by marvin            #+#    #+#             */
/*   Updated: 2021/04/27 11:40:01 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "cub3d.h"
#include "libft/libft.h"

int	sprite_text_parse(char *line, t_parse *parse)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split[1])
		return (0);
	parse->sprite_text = split[1];
	free(split);
	printf("parse->sprite_text = %s\n", parse->sprite_text);
	if (ft_strlen(parse->sprite_text) > 0)
		return (1);
	return (0);
}

int	floor_color_parse(char *line, t_parse *parse)
{
	char	**split;
	int		i;

	split = ft_split(line, ' ');
	split = ft_split(split[1], ',');
	if (!split[0] || !split[1] || !split[2])
		return (0);
	parse->floor_r = ft_atoi(split[0]);
	parse->floor_g = ft_atoi(split[1]);
	parse->floor_b = ft_atoi(split[2]);
	i = -1;
	while (++i <= 3)
		free(split[i]);
	free(split);
	if (parse->floor_r >= 0 && parse->floor_g >= 0
		&& parse->floor_b >= 0)
	{
		parse->floor_color = (parse->floor_r << 16) | (parse->floor_g << 8) | (parse->floor_b);
		printf("%x\n", parse->floor_color);
		return (1);
	}
	return (0);
}

int	ceiling_color_parse(char *line, t_parse *parse)
{
	char	**split;
	int		i;
	split = ft_split(line, ' ');
	split = ft_split(split[1], ',');
	if (!split[0] || !split[1] || !split[2])
		return (0);
	parse->ceil_r = ft_atoi(split[0]);
	parse->ceil_g = ft_atoi(split[1]);
	parse->ceil_b = ft_atoi(split[2]);
	i = -1;
	while (++i <= 3)
		free(split[i]);
	free(split);
	if (parse->ceil_r >= 0 && parse->ceil_g >= 0
		&& parse->ceil_b >= 0)
	{
		parse->ceil_color
			= (parse->ceil_r << 16) | (parse->ceil_g << 8) | (parse->ceil_b);
		printf("%x\n", parse->ceil_color);
		return (1);
	}
	return (0);
}
