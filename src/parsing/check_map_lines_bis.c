/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_lines_bis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:07:17 by iaschnei          #+#    #+#             */
/*   Updated: 2023/09/11 12:14:08 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	in_cset(char c);

int	check_around_zeros(char **map, int i)
{
	size_t		c_i;

	c_i = 0;
	while (map[i + 1] && map[i][0] != '\n')
	{
		c_i = 0;
		while (map[i][c_i] && map[i][c_i] != '\n')
		{
			if (map[i][c_i] == '0' || map[i][c_i] == 'N' || map[i][c_i] == 'S'
				|| map[i][c_i] == 'E' || map[i][c_i] == 'W')
			{
				if (!map[i - 1] || !map[i + 1])
					return (0);
				if (ft_strlen(map[i - 1]) <= c_i + 1
					|| ft_strlen(map[i + 1]) < c_i + 1 || c_i == 0)
					return (0);
				if (!in_cset(map[i][c_i + 1]) || !in_cset(map[i][c_i - 1])
					|| !in_cset(map[i + 1][c_i]) || !in_cset(map[i - 1][c_i]))
					return (0);
			}
			c_i++;
		}
		i++;
	}
	return (1);
}

static int	in_cset(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == '0' || c == '1')
		return (1);
	return (0);
}
