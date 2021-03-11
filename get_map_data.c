/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data->c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:28:49 by epfennig          #+#    #+#             */
/*   Updated: 2021/03/11 15:25:21 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "cub3d.h"
#include "libft/libft.h"

void	check_valid_map(char *line, t_data *data)
{
	(void)line;
	(void)data;
}

int	parse_line(char *line, t_data *data)
{
	char **split;

	printf("%s\n", line);
	if (ft_strnstr(line, "R", ft_strlen(line)))
		resolution_data(line, data);
	else if (ft_strnstr(line, "NO", ft_strlen(line)))
		north_text_data(line, data);
	else if (ft_strnstr(line, "SO", ft_strlen(line)))
		south_text_data(line, data);
	else if (ft_strnstr(line, "WE", ft_strlen(line)))
		south_text_data(line, data);
	else if (ft_strnstr(line, "EA", ft_strlen(line)))
		east_text_data(line, data);
	else if (ft_strnstr(line, "S", ft_strlen(line)))
	{
		split = ft_split(line, ' ');
		data->sprite_text = split[1];
		free(split);
		printf("data->sprite_text = %s\n", data->sprite_text);
		return (1);
	}
	else if (ft_strnstr(line, "F", ft_strlen(line)))
	{
		split = ft_split(line, ' ');
		split = ft_split(split[1], ',');
		data->floor_color_r = ft_atoi(split[0]);
		data->floor_color_g = ft_atoi(split[1]);
		data->floor_color_b = ft_atoi(split[2]);
		free(split);
		printf("data->floor_color_r = %i | data->floor_color_g = %i | data->floor_color_b = %i\n", data->floor_color_r, data->floor_color_g, data->floor_color_b);
		return (1);
	}
	else if (ft_strnstr(line, "C", ft_strlen(line)))
	{
		split = ft_split(line, ' ');
		split = ft_split(split[1], ',');
		data->ceiling_color_r = ft_atoi(split[0]);
		data->ceiling_color_g = ft_atoi(split[1]);
		data->ceiling_color_b = ft_atoi(split[2]);
		free(split);
		printf("data->ceiling_color_r = %i | data->ceiling_color_g = %i | data->ceiling_color_b = %i\n", data->ceiling_color_r, data->ceiling_color_g, data->ceiling_color_b);
		return (1);
	}
	return (0);
}

void	get_map_data(char *cub, t_data *data)
{
	int		fd;
	int		gnl;
	char	*line;

	gnl = 1;
	fd = open(cub, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: Can not open file");
		return ;
	}
	while (gnl > 0)
	{
		gnl = get_next_line(fd, &line);
		parse_line(line, data);
		if (gnl == 0)
			printf("Error: data in .cub is invalid\n");
	}
	printf("%s", line);
}
