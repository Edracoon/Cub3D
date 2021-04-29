/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 12:47:22 by epfennig          #+#    #+#             */
/*   Updated: 2021/04/29 18:37:38 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "cub3d.h"
#include "libft/libft.h"
int	is_dir(char c)
{
	if (c == 'N' || c == 'W' || c == 'N' || c == 'E')
		return (1);
	return (0);
}

void	check_char_zero(t_parse *p, int i, int j)
{
	int	good;

	good = 0;
	if (p->map[i - 1][j] == '1' || p->map[i - 1][j] == '0'
		|| is_dir(p->map[i - 1][j]) || p->map[i - 1][j] == '2')
		good++;
	if (p->map[i + 1][j] == '1' || p->map[i + 1][j] == '0'
		|| is_dir(p->map[i + 1][j]) || p->map[i + 1][j] == '2')
		good++;
	if (p->map[i][j + 1] == '1' || p->map[i][j + 1] == '0'
		|| is_dir(p->map[i][j + 1]) || p->map[i][j + 1] == '2')
		good++;
	if (p->map[i][j - 1] == '1' || p->map[i][j - 1] == '0'
		|| is_dir(p->map[i][j - 1]) || p->map[i][j - 1] == '2')
		good++;
	if (good != 4)
		ft_error("Error\nMap invalid in .cub\n", p);
}

void	check_map_valid(t_parse *p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	p->nbplayer = 0;
	while (p->sizecollum > i && p->map[i][j])
	{
		while (p->sizeline > j && p->map[i][j])
		{
			if (p->map[i][j] != ' ' && p->map[i][j] != '1' &&
					p->map[i][j] != '0' && p->map[i][j] != '2' &&
					!(is_dir(p->map[i][j])))
				ft_error("Error\nInvalid character in map.\n", p);
			if (p->map[i][j] == '0')
				check_char_zero(p, i, j);
			if (is_dir(p->map[i][j]))
			{
				check_char_zero(p, i, j);
				p->nbplayer++;
			}
			j++;
		}
		i++;
		j = 0;
	}
	if (p->nbplayer != 1)
		ft_error("Error\nNumber of player error\n", p);
}
