/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:18:39 by epfennig          #+#    #+#             */
/*   Updated: 2021/05/05 11:05:19 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line/get_next_line.h"
#include "../includes/cub3d.h"
#include "../libft/libft.h"

int	go_to_map(char *line)
{
	int	i;

	i = 0;
	if (ft_strnstr(line, "R", ft_strlen(line)))
		;
	else if (ft_strnstr(line, "NO", ft_strlen(line)))
		;
	else if (ft_strnstr(line, "SO", ft_strlen(line)))
		;
	else if (ft_strnstr(line, "WE", ft_strlen(line)))
		;
	else if (ft_strnstr(line, "EA", ft_strlen(line)))
		;
	else if (ft_strnstr(line, "S", ft_strlen(line)))
		;
	else if (ft_strnstr(line, "F", ft_strlen(line)))
		;
	else if (ft_strnstr(line, "C", ft_strlen(line)))
		;
	else if (line[i] == '\n' || !ft_strnstr(line, "1", ft_strlen(line)))
		return (1);
	else if (ft_strnstr(line, "1", ft_strlen(line)))
		return (2);
	i = 3;
	return (i);
}

void	size_map_malloc(char *line, t_parse *p, int fd, int gnl)
{
	int	i;
	int	j;

	i = 0;
	p->sizecollum += 1;
	while (gnl > 0)
	{
		j = 0;
		while (line[j] != '\0')
		{
			j++;
			if (j > p->sizeline)
				p->sizeline += 1;
		}
		i++;
		p->sizecollum += 1;
		free(line);
		line = NULL;
		gnl = get_next_line(fd, &line);
	}
	free(line);
	line = NULL;
	p->map = (char **)malloc(sizeof(char *) * (p->sizecollum));
	if (!(p->map))
		ft_error("Error\nmap malloc error\n", p);
}

int	get_fd(char *cub, t_parse *p)
{
	int	fd;

	fd = open(cub, O_DIRECTORY);
	if (fd > 0)
		ft_error("Error\nYou are trying to open a directory\n", p);
	fd = open(cub, O_RDONLY);
	if (fd == -1)
		ft_error("Error\nCan not open file\n", p);
	return (fd);
}

int	check_last_time_cub(t_parse *parse)
{
	if (!parse->west_text || !parse->north_text
		|| !parse->south_text || !parse->east_text
		|| !parse->sprite_text || parse->floor_r < 0
		|| parse->floor_g < 0 || parse->floor_b < 0
		|| parse->ceil_r < 0 || parse->ceil_g < 0
		|| parse->ceil_b < 0 || parse->win_x <= 0 || parse->win_y <= 0)
		return (0);
	return (1);
}
