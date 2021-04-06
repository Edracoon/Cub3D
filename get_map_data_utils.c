/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 16:05:45 by epfennig          #+#    #+#             */
/*   Updated: 2021/04/06 16:57:25 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "cub3d.h"
#include "libft/libft.h"

int	resolution_parse(char *line, t_parse *parse)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split[1] || !split[2])
		return (0);
	parse->win_x = ft_atoi(split[1]);
	parse->win_y = ft_atoi(split[2]);
	free(split);
	printf("x = %i | y = %i\n", parse->win_x, parse->win_y);
	if (parse->win_x > 0 && parse->win_y > 0)
		return (1);
	return (0);
}

int	north_text_parse(char *line, t_parse *parse)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split[1])
		return (0);
	parse->north_text = split[1];
	free(split);
	printf("parse->north_text = %s\n", parse->north_text);
	if (ft_strlen(parse->north_text) > 0)
		return (1);
	return (0);
}

int	east_text_parse(char *line, t_parse *parse)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split[1])
		return (0);
	parse->east_text = split[1];
	free(split);
	printf("parse->east_text = %s\n", parse->east_text);
	if (ft_strlen(parse->east_text) > 0)
		return (1);
	return (0);
}

int	west_text_parse(char *line, t_parse *parse)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split[1])
		return (0);
	parse->west_text = split[1];
	free(split);
	printf("parse->west_text = %s\n", parse->west_text);
	if (ft_strlen(parse->west_text) > 0)
		return (1);
	return (0);
}

int	south_text_parse(char *line, t_parse *parse)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split[1])
		return (0);
	parse->south_text = split[1];
	free(split);
	printf("parse->south_text = %s\n", parse->south_text);
	if (ft_strlen(parse->south_text) > 0)
		return (1);
	return (0);
}
