/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:28:49 by epfennig          #+#    #+#             */
/*   Updated: 2021/04/28 18:21:59 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "cub3d.h"
#include "libft/libft.h"

void	ft_error(char *str, t_parse *p)
{
	(void)p;
	printf("%s", str);
	exit(0);
}

void	stockage_map2(t_parse *p, int i, char *line)
{
	int		j;

	j = 0;
	p->map[i] = (char *)malloc(sizeof(char) * (p->sizeline + 1));
	if (!(p->map[i]))
		ft_error("Error\nmap malloc error\n", p);
	while (line[j] != '\0')
	{
		p->map[i][j] = line[j];
		j++;
	}
	p->map[i][j] = '\0';
	printf("%s\n", p->map[i]);
	free(line);
	line = NULL;
}

void	stockage_map(char *cub, t_parse *p, int fd)
{
	int		i;
	char	*line;
	int		gnl;
	int		retu;

	fd = get_fd(cub, p);
	gnl = 1;
	while (gnl > 0)
	{
		gnl = get_next_line(fd, &line);
		retu = go_to_map(line);
		if (retu == 0)
			break ;
		if (retu == 2)
			break ;
		free(line);
		line = NULL;
	}
	i = -1;
	while (gnl > 0)
	{
		stockage_map2(p, ++i, line);
		gnl = get_next_line(fd, &line);
	}
	parse_map(p);
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

void	get_map_parse(char *cub, t_parse *p)
{
	int		fd;
	int		gnl;
	int		retu;
	char	*line;

	gnl = 1;
	fd = get_fd(cub, p);
	while (gnl > 0)
	{
		gnl = get_next_line(fd, &line);
		retu = parse_line(line, p);
		if (retu == 0)
			break ;
		if (retu == 2)
			break ;
		free(line);
		line = NULL;
	}
	if (gnl != 0 && retu != 2)
		ft_error("Error\nParse in .cub is invalid\n", p);
	if (check_last_time_cub(p) == 0)
		ft_error("Error\nParse in .cub is invalid\n", p);
	size_map_malloc(line, p, fd, gnl);
	stockage_map(cub, p, fd);
	mlx_main(p);
}
