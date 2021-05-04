/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_random.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 16:13:11 by epfennig          #+#    #+#             */
/*   Updated: 2021/05/04 16:05:31 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line/get_next_line.h"
#include "../includes/cub3d.h"
#include "../libft/libft.h"

int	is_num_boucle(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
	return (1);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab[i]);
	free(tab);
}

int	check_retu(int retu)
{
	if (retu == 0 || retu == 2)
		return (1);
	return (0);
}

void	ft_error(char *str, t_parse *p)
{
	(void)p;
	printf("%s", str);
	exit(0);
}

void	get_textu_addr(t_parse *p)
{
	int	x;

	x = -1;
	while (++x <= 4)
		p->textu[x].addr = mlx_get_data_addr(p->textu[x].img, \
			&p->textu[x].bits_per_pixel,
				&p->textu[x].line_length, &p->textu[x].endian);
}
