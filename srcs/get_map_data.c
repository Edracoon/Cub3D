/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:28:49 by epfennig          #+#    #+#             */
/*   Updated: 2021/05/04 10:40:55 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line/get_next_line.h"
#include "../includes/cub3d.h"
#include "../libft/libft.h"

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
	{
		free(line);
		ft_error("Error\nmap malloc error\n", p);
	}
	while (line[j] != '\0')
	{
		p->map[i][j] = line[j];
		j++;
	}
	p->map[i][j] = '\0';
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
		if (retu == 2)
			break ;
		free(line);
		line = NULL;
	}
	i = 0;
	while (gnl > 0)
	{
		stockage_map2(p, i, line);
		gnl = get_next_line(fd, &line);
		i++;
	}
	stockage_map2(p, i, line);
	i = -1;
	parse_map(p);
}

int	parse_line(char *line, t_parse *parse)
{
	int	i;
	char	**split;

	split = ft_split(line, ' ');
	i = 0;
	if (split[0] && !ft_strncmp(split[0], "R", 2))
		i = resolution_parse(line, parse);
	else if (split[0] && !ft_strncmp(split[0], "NO", 3))
		i = north_text_parse(line, parse);
	else if (split[0] && !ft_strncmp(split[0], "SO", 3))
		i = south_text_parse(line, parse);
	else if (split[0] && !ft_strncmp(split[0], "WE", 3))
		i = west_text_parse(line, parse);
	else if (split[0] && !ft_strncmp(split[0], "EA", 3))
		i = east_text_parse(line, parse);
	else if (split[0] && !ft_strncmp(split[0], "S", 2))
		i = sprite_text_parse(line, parse);
	else if (split[0] && !ft_strncmp(split[0], "F", 2))
		i = floor_color_parse(split[1], parse);
	else if (split[0] && !ft_strncmp(split[0], "C", 2))
		i = ceiling_color_parse(split[1], parse);
	else if (line[i] == '\0')
	{
		free_tab(split);
		return (1);
	}
	else if (ft_strnstr(line, "1", ft_strlen(line)))
	{
		free_tab(split);
		return (2);
	}
	free_tab(split);
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
		if (check_retu(retu) == 1)
			break ;
		free(line);
		line = NULL;
	}
	if (retu == 0)
		free(line);
	if (gnl != 0 && retu != 2)
		ft_error("Error\nParse in .cub is invalid\n", p);
	if (check_last_time_cub(p) == 0)
		ft_error("Error\nParse in .cub is invalid\n", p);
	size_map_malloc(line, p, fd, gnl);
	stockage_map(cub, p, fd);
	mlx_main(p);
}
