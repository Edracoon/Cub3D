/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:28:49 by epfennig          #+#    #+#             */
/*   Updated: 2021/04/26 16:18:16 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "cub3d.h"
#include "libft/libft.h"

int	get_fd(char *cub)
{
	int	fd;

	fd = open(cub, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: Can not open file");
		return (-1);
	}
	return (fd);
}

int	check_last_time_cub(t_parse *parse)
{
	if (!parse->west_text || !parse->north_text
		|| !parse->south_text || !parse->east_text
		|| !parse->sprite_text || parse->floor_r < 0
		|| parse->floor_g < 0 || parse->floor_b < 0
		|| parse->ceil_r < 0 || parse->ceil_g < 0
		|| parse->ceil_b < 0)
		return (0);
	return (1);
}

void	stockage_map(char *line, t_parse *parse, int fd, int gnl)
{
	int	i;
	int	j;

	i = 0;
	while (gnl > 0)
	{
		j = 0;
		while (line[j] != '\0')
		{
			parse->map[i][j] = line[j];
			j++;
		}
		parse->map[i][j] = '\0';
		printf("%s\n", parse->map[i]);
		gnl = get_next_line(fd,	&line);
		i++;
	}
	parse_map(parse);
	return ;
}

int	parse_line(char *line, t_parse *parse)
{
	int	i;

	i = 0;
	if (ft_strnstr(line, "R", ft_strlen(line)))
		i = resolution_parse(line, parse);
	else if (ft_strnstr(line, "NO", ft_strlen(line)))
		i = north_text_parse(line, parse);
	else if (ft_strnstr(line, "SO", ft_strlen(line)))
		i = south_text_parse(line, parse);
	else if (ft_strnstr(line, "WE", ft_strlen(line)))
		i = west_text_parse(line, parse);
	else if (ft_strnstr(line, "EA", ft_strlen(line)))
		i = east_text_parse(line, parse);
	else if (ft_strnstr(line, "S", ft_strlen(line)))
		i = sprite_text_parse(line, parse);
	else if (ft_strnstr(line, "F", ft_strlen(line)))
		i = floor_color_parse(line, parse);
	else if (ft_strnstr(line, "C", ft_strlen(line)))
		i = ceiling_color_parse(line, parse);
	else if (line[i] == '\n' || !ft_strnstr(line, "1", ft_strlen(line)))
		return (1);
	else if (ft_strnstr(line, "1", ft_strlen(line)))
		return (2);
	return (i);
}

void	get_map_parse(char *cub, t_parse *parse)
{
	int		fd;
	int		gnl;
	int		retu;
	char	*line;

	gnl = 1;
	fd = get_fd(cub);
	if (fd == -1)
		return ;
	while (gnl > 0)
	{
		gnl = get_next_line(fd, &line);
		retu = parse_line(line, parse);
		if (retu == 0)
			break ;
		if (retu == 2)
			break ;
	}
	if (gnl != 0 && retu != 2)
	{
		printf("Error: parse in .cub is invalid\n");
		return ;
	}
	if (check_last_time_cub(parse) == 0)
	{
		printf("Error: parse in .cub is invalid\n");
		return ;
	}
	stockage_map(line, parse, fd, gnl);
	mlx_main(parse);
}
