/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 11:46:54 by epfennig          #+#    #+#             */
/*   Updated: 2021/05/05 11:30:28 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line/get_next_line.h"
#include "../includes/cub3d.h"
#include "../libft/libft.h"

int	check_map_name(char *av)
{
	int	len;

	len = ft_strlen(av);
	len -= 4;
	av = ft_substr(av, len, 4);
	if ((ft_strnstr(av, ".cub", 4)))
	{
		free(av);
		return (1);
	}
	free(av);
	return (0);
}

void	init_struc2(t_parse *p)
{
	p->arg_save = 0;
	p->kill_win = 0;
	p->forward = 0;
	p->backward = 0;
	p->leftward = 0;
	p->rightward = 0;
	p->north_text = NULL;
	p->south_text = NULL;
	p->west_text = NULL;
	p->east_text = NULL;
	p->sprite_text = NULL;
	p->sizeline = 0;
	p->sizecollum = 0;
	p->nbplayer = 0;
}

void	init_parse_struct(t_parse *p)
{
	p->ratio = 0.0;
	p->dirx = -1;
	p->diry = 0;
	p->planex = 0;
	p->planey = 0.66;
	p->win_x = 0;
	p->win_y = 0;
	p->floor_r = -1;
	p->floor_g = -1;
	p->floor_b = -1;
	p->ceil_r = -1;
	p->ceil_g = -1;
	p->ceil_b = -1;
	p->reso = 0;
	p->no = 0;
	p->so = 0;
	p->we = 0;
	p->ea = 0;
	p->s = 0;
	p->f = 0;
	p->c = 0;
	init_struc2(p);
}

int	main(int ac, char *av[])
{
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	if (!(parse))
		return (-1);
	init_parse_struct(parse);
	if (ac < 2)
		ft_error("Error\ntoo few arguments\n", parse);
	if (ac > 3)
		ft_error("Error\ntoo many arguments\n", parse);
	if (ac == 3 && ft_strncmp(av[2], "--save", 6) == 0)
		parse->arg_save = 1;
	else if (ac == 3 && av[2])
		ft_error("Error\n-> arg[2] must be '--save'\n", parse);
	if (check_map_name(av[1]) == 1)
		get_map_parse(av[1], parse);
	else
		printf("Error\n-> map name is invalid\n");
	return (0);
}
