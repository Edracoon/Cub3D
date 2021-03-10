/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 11:46:54 by epfennig          #+#    #+#             */
/*   Updated: 2021/03/10 14:01:56 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "cub3d.h"

int			check_map_name(char *av)
{
	int len;

	len = ft_strlen(av);
	if ((*av = ft_strnstr(av, ".cub", len) != 0))
	{
		if (*av++ == '\0')
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

int			main(int ac, char *av[])
{
	t_data	data;

	if (ac < 2)
	{
		printf("error: too few arguments\n");
		return (0);
	}
	if (ac > 3)
	{
		printf("error: too many arguments\n");
		return (0);
	}
	if (ac == 3 && ft_strncmp(av[2], "--save", ft_strlen(av[2])) == 0)
		data.arg_save = 1;
	else if (ac == 3 && av[2])
	{
		printf("error: av[2] must be '--save'\n");
		return (0);
	}
	if (check_map_name(av[1]) == 1)
		printf("c'est bon\n");
	else
		printf("error: map name is invalid\n");
	return (0);
}
