/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_useless_lines.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 09:53:21 by iaschnei          #+#    #+#             */
/*   Updated: 2023/09/11 11:38:41 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//Check that there are no useless lines ->
// check every line before the map that is not starting
// by NO, SO, EA, WE, C or F
//* Empty lines must be a '\n' only
int	check_useless_lines(char **map)
{
	int	iter;
	int	max;
	int	c_iter;

	iter = 0;
	max = find_first_line(map);
	while (map[iter] && iter < max)
	{
		c_iter = 0;
		while (map[iter][c_iter] == ' ')
			c_iter++;
		if (is_text_identifier(map, iter, c_iter)
			|| (map[iter][c_iter] == 'C' && map[iter][c_iter + 1] == ' ')
			|| (map[iter][c_iter] == 'F' && map[iter][c_iter + 1] == ' '))
		{
			iter++;
			continue ;
		}
		else if (map[iter][0] != '\n')
			return (0);
		iter++;
	}
	return (1);
}

int	is_text_identifier(char **map, int line, int c_i)
{
	if (map[line][c_i + 1])
	{
		if ((map[line][c_i] == 'N' && map[line][c_i + 1] == 'O')
			|| (map[line][c_i] == 'S' && map[line][c_i + 1] == 'O')
			|| (map[line][c_i] == 'W' && map[line][c_i + 1] == 'E')
			|| (map[line][c_i] == 'E' && map[line][c_i + 1] == 'A'))
			return (1);
	}
	return (0);
}

void	fill_buffer(char *buffer, char *line, int begin, int iter)
{
	while (line[iter + begin + 3] && line[iter + begin + 3] != '\n')
	{
		buffer[iter] = line[iter + begin + 3];
		iter++;
	}
	buffer[iter] = 0;
}
