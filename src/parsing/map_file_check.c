/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:58:11 by iaschnei          #+#    #+#             */
/*   Updated: 2023/09/06 15:50:04 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	**read_map_file(char *path);
static int	check_file(char **map);

// Will check the map file :
// - Only valid and expected lines
// - Correct textures and colors
// - Correct map (closed and player)
// ! This function does not assign anything to data to simplify cleanup if err
// ! Everything alloced here should be freed here

//TODO: Check for useless lines
char	**incorrect_map_file(char **av)
{
	char	**map;

	map = read_map_file(av[1]);
	if (!map)
		return (NULL);
	if (!check_file(map))
	{
		free_tab(map);
		return (NULL);
	}
	return (map);
}

// Read from the map file and put it in a chained list
// Because we don't know how long the file is gonna be
// Then convert from a list to a char ** for the parsing
// ! The char ** contains every line from the file not only the map
static char	**read_map_file(char *path)
{
	t_list	*map_list;
	char	*line;
	char	**ret;
	int		fd;

	fd = open(path, O_RDONLY);
	map_list = NULL;
	line = get_next_line(fd);
	while (line)
	{
		ft_lstadd_back(&map_list, ft_lstnew(ft_strdup(line)));
		free(line);
		line = get_next_line(fd);
	}
	ret = from_list_to_arr(map_list);
	ft_lstclear(&map_list, free);
	close(fd);
	if (!ret)
		return (NULL);
	return (ret);
}

// Transform the chained list into a char **
// Checking for intermediate errors and handling them
char	**from_list_to_arr(t_list *map_list)
{
	char	**ret;
	int		iter;

	iter = 0;
	ret = malloc((ft_lstsize(map_list) + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	while (map_list)
	{
		ret[iter] = ft_strdup(map_list->content);
		if (!ret[iter])
		{
			iter = 0;
			while (ret[iter])
			{
				free(ret[iter]);
				iter++;
			}
			return (free(ret), NULL);
		}
		map_list = map_list->next;
		iter++;
	}
	ret[iter] = NULL;
	return (ret);
}

static int	check_file(char **map)
{
	if (!check_text_lines(map))
		return (0);
	if (!check_map_lines(map))
		return (0);
	if (!check_useless_lines(map))
		return (0);
	return (1);
}

int	find_last_line(char **map, int iter)
{
	while (map[iter + 1])
		iter++;
	return (iter);
}
