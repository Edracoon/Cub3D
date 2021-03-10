/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 11:46:54 by epfennig          #+#    #+#             */
/*   Updated: 2021/03/10 17:37:23 by epfennig         ###   ########.fr       */
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

int	main(int ac, char *av[])
{
	t_data	data;

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
		data.arg_save = 1;
	else if (ac == 3 && av[2])
	{
		printf("Error: av[2] must be '--save'\n");
		return (0);
	}
	if (check_map_name(av[1]) == 1)
		get_map_data(av[1], data);
	else
		printf("Error: map name is invalid\n");
	return (0);
}
