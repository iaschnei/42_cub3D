/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_text_lines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:17:21 by iaschnei          #+#    #+#             */
/*   Updated: 2023/09/11 13:41:21 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	test_paths(char **map);
static int	search_path_and_try(char *line, int begin);
static int	check_colors(char **map);
static int	check_rgb(char *line, int begin);

//This will check if the textures path are correct (and if the colors of the
//floor and ceiling are valid)
int	check_text_lines(char **map)
{
	if (!test_paths(map))
		return (0);
	if (!check_colors(map))
		return (0);
	return (1);
}

//Parse the file to find lines where there should be a text path
static int	test_paths(char **map)
{
	int	line_i;
	int	c_i;
	int	correct_paths;

	line_i = 0;
	correct_paths = 0;
	while (map[line_i])
	{
		c_i = 0;
		if (ft_strlen(map[line_i]) > 2)
		{
			while (map[line_i][c_i] == ' ')
				c_i++;
			if (is_text_identifier(map, line_i, c_i))
			{
				if (search_path_and_try(map[line_i], c_i))
					correct_paths++;
			}
		}
		line_i++;
	}
	if (correct_paths != 4)
		return (0);
	return (1);
}

//Copy the path after the identifier and try to open the file
static int	search_path_and_try(char *line, int begin)
{
	int		iter;
	int		fd;
	char	*buffer;
	char	*buffer_trimmed;

	iter = 0;
	if (ft_strlen(line) < (size_t)(4 + begin))
		return (0);
	if (line[begin + 2] != ' ')
		return (0);
	buffer = malloc((ft_strlen(line) - begin - 2) * sizeof(char));
	if (!buffer)
		return (0);
	fill_buffer(buffer, line, begin, iter);
	buffer_trimmed = ft_strtrim(buffer, " ");
	free(buffer);
	fd = open(buffer_trimmed, O_RDONLY);
	free(buffer_trimmed);
	if (fd == -1)
		return (0);
	if (read(fd, NULL, 0) == -1)
		return (close(fd), 0);
	return (close(fd), 1);
}

//Check that the color codes for the Ceiling and Floor are correct
static int	check_colors(char **map)
{
	int	line_iter;
	int	c_i;

	line_iter = 0;
	while (map[line_iter])
	{
		c_i = 0;
		while (map[line_iter][c_i] == ' ')
			c_i++;
		if (map[line_iter][c_i] == 'C' || map[line_iter][c_i] == 'F')
		{
			if (ft_strlen(map[line_iter]) < (size_t)(8 + c_i))
				return (0);
			c_i++;
			if (map[line_iter][c_i] != ' ')
				return (0);
			while (map[line_iter][c_i] == ' ')
				c_i++;
			if (!check_rgb(map[line_iter], c_i))
				return (0);
		}
		line_iter++;
	}
	return (1);
}

//Check the numbers after the C or F indicator
static int	check_rgb(char *line, int begin)
{
	int	iter;
	int	digit_count;
	int	number_count;

	iter = 0;
	number_count = 0;
	while (line[iter + begin] && line[iter + begin] != ' ')
	{
		digit_count = 0;
		while (line[iter + begin] && line[iter + begin] != ','
			&& line[iter + begin] != '\n' && line[iter + begin] != ' ')
		{
			if (line[iter + begin] < '0' || line[iter + begin] > '9')
				return (0);
			digit_count++;
			iter++;
		}
		number_count++;
		if (digit_count > 3 || digit_count == 0)
			return (0);
		iter++;
	}
	if (number_count != 3)
		return (0);
	return (1);
}
