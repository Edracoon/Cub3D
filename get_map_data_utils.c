/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 16:05:45 by epfennig          #+#    #+#             */
/*   Updated: 2021/04/30 12:05:33 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "cub3d.h"
#include "libft/libft.h"

int	resolution_parse(char *line, t_parse *parse)
{
	char	**split;

	parse->reso += 1;
	if (parse->reso > 1)
		ft_error("Error\nMore than one 'R' in .cub\n", parse);
	split = ft_split(line, ' ');
	if (!split[1] || !split[2])
		return (0);
	if (!(is_num_boucle(split[1])) || (!(is_num_boucle(split[2]))))
		ft_error("Error\nResolution error in .cub\n", parse);
	if (split[3])
	{
		free(split);
		ft_error("Error\nResolution can only take 2 parameters in .cub\n", parse);
	}
	parse->win_x = ft_atoi(split[1]);
	parse->win_y = ft_atoi(split[2]);
	free(split[0]);
	free(split[1]);
	free(split[2]);
	if (parse->win_x > 0 && parse->win_y > 0)
		return (1);
	return (0);
}

int	north_text_parse(char *line, t_parse *parse)
{
	char	**split;

	parse->no += 1;
	if (parse->no > 1)
		ft_error("Error\ntwo north texture\n", parse);
	split = ft_split(line, ' ');
	free(split[0]);
	if (!split[1] || split[2])
		ft_error("Error\nNorth texture: too much parameters\n", parse);
	parse->north_text = split[1];
	free(split);
	if (ft_strlen(parse->north_text) > 0)
		return (1);
	return (0);
}

int	east_text_parse(char *line, t_parse *parse)
{
	char	**split;

	parse->ea += 1;
	if (parse->ea > 1)
		ft_error("Error\ntwo east texture\n", parse);
	split = ft_split(line, ' ');
	free(split[0]);
	if (!split[1] || split[2])
		ft_error("Error\nEast texture: too much parameters\n", parse);
	parse->east_text = split[1];
	free(split);
	if (ft_strlen(parse->east_text) > 0)
		return (1);
	return (0);
}

int	west_text_parse(char *line, t_parse *parse)
{
	char	**split;

	parse->we += 1;
	if (parse->we > 1)
		ft_error("Error\ntwo west texture\n", parse);
	split = ft_split(line, ' ');
	free(split[0]);
	if (!split[1] || split[2])
		ft_error("Error\nWest texture: too much parameters\n", parse);
	parse->west_text = split[1];
	free(split);
	if (ft_strlen(parse->west_text) > 0)
		return (1);
	return (0);
}

int	south_text_parse(char *line, t_parse *parse)
{
	char	**split;

	parse->so += 1;
	if (parse->so > 1)
		ft_error("Error\ntwo south texture\n", parse);
	split = ft_split(line, ' ');
	free(split[0]);
	if (!split[1] || split[2])
		ft_error("Error\nSouth texture: too much parameters\n", parse);
	parse->south_text = split[1];
	free(split);
	if (ft_strlen(parse->south_text) > 0)
		return (1);
	return (0);
}
