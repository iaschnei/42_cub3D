/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:20:56 by iaschnei          #+#    #+#             */
/*   Updated: 2023/09/11 13:37:08 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_first_map_line(char **map, int i);
static int	check_last_map_line(char **map, int i);
static int	check_interm_map_lines(char **map, int i);
static int	check_space(char **map, int i, int c_i);

//This will check if the map is correct (closed and only valid chars)
int	check_map_lines(char **map)
{
	int	first_line_index;

	first_line_index = find_first_line(map);
	if (first_line_index == -1)
		return (0);
	if (!check_first_map_line(map, first_line_index))
		return (0);
	if (!check_interm_map_lines(map, first_line_index + 1))
		return (0);
	if (!check_around_zeros(map, first_line_index + 1))
		return (0);
	if (!check_last_map_line(map, first_line_index))
		return (0);
	return (1);
}

//Check that:
// -There are at least two lines after the first of the map
// -This first line is only '1' or spaces
// -Spaces are surrounded by spaces or '1' only (or '\n' for the last char)
// i = index and c_i = char_iter
static int	check_first_map_line(char **map, int i)
{
	int	c_i;

	if (!map[i + 1] || !map[i + 2])
		return (0);
	c_i = 0;
	while (map[i][c_i] && map[i][c_i] != '\n')
	{
		if (map[i][c_i] != ' ' && map[i][c_i] != '1')
			return (0);
		if (map[i][c_i] == ' ')
		{
			if ((map[i + 1][c_i] != ' ' && map[i + 1][c_i] != '1')
				|| (map[i][c_i + 1] != ' ' && map[i][c_i + 1] != '1'
				&& map[i][c_i + 1] != '\n'))
				return (0);
			if (c_i > 0 && map[i][c_i - 1] != ' ' && map[i][c_i - 1] != '1')
				return (0);
		}
		c_i++;
	}
	return (1);
}

//Check that:
// -This last line is only '1' or spaces
// -Spaces are surrounded by spaces or '1' only (or '\n' for the last char)
// i = index and c_i = char_iter
//*No extra lines are allowed after the map. The file must end with this line
static int	check_last_map_line(char **map, int i)
{
	size_t	c_i;

	c_i = 0;
	i = find_last_line(map, i + 1);
	while (map[i][c_i] && map[i][c_i] != '\n')
	{
		if (map[i][c_i] != ' ' && map[i][c_i] != '1')
			return (0);
		if (map[i][c_i] == ' ')
		{
			if (ft_strlen(map[i - 1]) <= c_i + 1)
				return (0);
			if ((map[i - 1][c_i] != ' ' && map[i - 1][c_i] != '1')
				|| (map[i][c_i + 1] != ' ' && map[i][c_i + 1] != '1'
				&& map[i][c_i + 1] != '\n'))
				return (0);
			if (c_i > 0 && map[i][c_i - 1] != ' ' && map[i][c_i - 1] != '1')
				return (0);
		}
		c_i++;
	}
	if (map[i + 1])
		return (0);
	return (1);
}

static int	check_interm_map_lines(char **map, int i)
{
	int	c_i;
	int	spawn_count;

	spawn_count = 0;
	while (map[i + 1] && map[i][0] != '\n')
	{
		c_i = 0;
		while (map[i][c_i] && map[i][c_i] != '\n')
		{
			if (map[i][c_i] != ' ' && map[i][c_i] != '1' && map[i][c_i] != '0'
				&& map[i][c_i] != 'N' && map[i][c_i] != 'S'
				&& map[i][c_i] != 'E' && map[i][c_i] != 'W')
				return (0);
			if (map[i][c_i] == 'N' || map[i][c_i] == 'S'
				|| map[i][c_i] == 'E' || map[i][c_i] == 'W')
				spawn_count++;
			if (map[i][c_i] == ' ' && !check_space(map, i, c_i))
				return (0);
			c_i++;
		}
		i++;
	}
	if (spawn_count != 1)
		return (0);
	return (1);
}

static int	check_space(char **map, int i, int c_i)
{
	int	only_space;

	only_space = 1;
	if ((map[i - 1][c_i] != ' ' && map[i - 1][c_i] != '1')
		|| (map[i + 1][c_i] != ' ' && map[i + 1][c_i] != '1')
		|| (map[i][c_i + 1] != ' ' && map[i][c_i + 1] != '1'
		&& map[i][c_i + 1] != '\n'))
		return (0);
	if (c_i > 0 && map[i][c_i - 1] != ' ' && map[i][c_i - 1] != '1')
		return (0);
	while (map[i][c_i] && map[i][c_i] != '\n')
	{
		if (map[i][c_i] != ' ')
			only_space = 0;
		c_i++;
	}
	if (only_space == 1)
		return (0);
	return (1);
}
