/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:28:49 by epfennig          #+#    #+#             */
/*   Updated: 2021/03/10 17:39:20 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "cub3d.h"

void	parse_line(char *line, t_data data)
{
	(void)data;
	printf("%s", line);
}

void	get_map_data(char *cub, t_data data)
{
	int	fd;
	int	gnl;
	char *line;

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
	}
}
