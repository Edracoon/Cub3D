/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 16:05:45 by epfennig          #+#    #+#             */
/*   Updated: 2021/03/11 18:13:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "cub3d.h"
#include "libft/libft.h"

int	resolution_data(char *line, t_data *data)
{
	char	**split;

	split = ft_split(line, ' ');
	data->rendu_x = ft_atoi(split[1]);
	data->rendu_y = ft_atoi(split[2]);
	free(split);
	printf("x = %i | y = %i\n", data->rendu_x, data->rendu_y);
	if (data->rendu_x > 0 && data->rendu_y > 0)
		return (1);
	return (0);
}

int	north_text_data(char *line, t_data *data)
{
	char	**split;

	split = ft_split(line, ' ');
	data->north_text = split[1];
	free(split);
	printf("data->north_text = %s\n", data->north_text);
	if (ft_strlen(data->north_text) > 0)
		return (1);
	return (0);
}

int	east_text_data(char *line, t_data *data)
{
	char	**split;

	split = ft_split(line, ' ');
	data->east_text = split[1];
	free(split);
	printf("data->east_text = %s\n", data->east_text);
	if (ft_strlen(data->east_text) > 0)
		return (1);
	return (0);
}

int	west_text_data(char *line, t_data *data)
{
	char	**split;

	split = ft_split(line, ' ');
	data->west_text = split[1];
	free(split);
	printf("data->west_text = %s\n", data->west_text);
	if (ft_strlen(data->west_text) > 0)
		return (1);
	return (0);
}

int	south_text_data(char *line, t_data *data)
{
	char	**split;

	split = ft_split(line, ' ');
	data->south_text = split[1];
	free(split);
	printf("data->south_text = %s\n", data->south_text);
	if (ft_strlen(data->south_text) > 0)
		return (1);
	return (0);
}
