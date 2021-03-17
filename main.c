/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 11:46:54 by epfennig          #+#    #+#             */
/*   Updated: 2021/03/17 14:00:16 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "cub3d.h"

int	check_map_name(char *av)
{
	int	len;

	len = ft_strlen(av);
	len -= 4;
	av = ft_substr(av, len, 4);
	if (ft_strncmp(av, ".cub", 4) == 0)
		return (1);
	return (0);
}

void	init_parse_struct(t_parse *parse)
{
	parse->win_x = 0;
	parse->win_y = 0;
	parse->per_x = 0;
	parse->per_y = 0;
	parse->floor_r = -1;
	parse->floor_g = -1;
	parse->floor_b = -1;
	parse->ceil_r = -1;
	parse->ceil_g = -1;
	parse->ceil_b = -1;
	parse->arg_save = 0;
	parse->north_text = NULL;
	parse->south_text = NULL;
	parse->west_text = NULL;
	parse->east_text = NULL;
	parse->sprite_text = NULL;
}

int	main(int ac, char *av[])
{
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	if (!(parse))
		return (-1);
	init_parse_struct(parse);
	if (ac < 2)
	{
		printf("Error: too few arguments\n");
		return (0);
	}
	if (ac > 3)
	{
		printf("Error: too many arguments\n");
		return (0);
	}
	if (ac == 3 && ft_strncmp(av[2], "--save", ft_strlen(av[2])) == 0)
		parse->arg_save = 1;
	else if (ac == 3 && av[2])
	{
		printf("Error: av[2] must be '--save'\n");
		return (0);
	}
	if (check_map_name(av[1]) == 1)
		get_map_parse(av[1], parse);
	else
		printf("Error: map name is invalid\n");
	return (0);
}
