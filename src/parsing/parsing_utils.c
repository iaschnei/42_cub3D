/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 09:43:19 by iaschnei          #+#    #+#             */
/*   Updated: 2023/09/11 13:33:56 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//Looks for the first '1' character in the map except for
//the lines with a texture or a color
int	find_first_line(char **map)
{
	int	iter;
	int	char_iter;

	iter = 0;
	while (map[iter])
	{
		char_iter = 0;
		while (map[iter][char_iter] == ' ')
			char_iter++;
		if (map[iter][char_iter] != 'N' && map[iter][char_iter] != 'S'
			&& map[iter][char_iter] != 'W' && map[iter][char_iter] != 'E'
			&& map[iter][char_iter] != 'C' && map[iter][char_iter] != 'F')
		{
			while (map[iter][char_iter])
			{
				if (map[iter][char_iter] == '1')
					return (iter);
				char_iter++;
			}
		}
		iter++;
	}
	return (-1);
}

// Extract only the map from the file
char	**extract_map(char **file)
{
	char	**ret;
	int		iter;
	int		tmp;

	tmp = 0;
	while (file[tmp])
		tmp++;
	iter = find_first_line(file);
	ret = malloc((tmp - iter + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	tmp = 0;
	while (file[iter + tmp])
	{
		ret[tmp] = ft_strdup(file[iter + tmp]);
		if (!ret[tmp])
			return (NULL);
		tmp++;
	}
	ret[tmp] = 0;
	return (ret);
}

// Check that no malloc failed during assignation to t_textures
// If one failed, check and free the ones that worked
int	check_malloc(t_textures *tex)
{
	if (!tex->north_text || !tex->south_text || !tex->east_text
		|| !tex->west_text || !tex->ceil_col || !tex->floor_col)
	{
		if (tex->north_text)
			free(tex->north_text);
		if (tex->south_text)
			free(tex->south_text);
		if (tex->east_text)
			free(tex->east_text);
		if (tex->west_text)
			free(tex->west_text);
		if (tex->floor_col)
			free(tex->floor_col);
		if (tex->ceil_col)
			free(tex->ceil_col);
		return (1);
	}
	return (0);
}

void	initialise_text(t_textures *tex)
{
	tex->north_text = NULL;
	tex->south_text = NULL;
	tex->east_text = NULL;
	tex->west_text = NULL;
	tex->floor_col = NULL;
	tex->ceil_col = NULL;
	tex->north_tab = NULL;
	tex->south_tab = NULL;
	tex->east_tab = NULL;
	tex->west_tab = NULL;
}

/// by checking the character corresponding to a cardinal orientation,
///	returns its orientation angle beta in radians.
float	get_spawn_beta(char c)
{
	if (c == 'E')
		return (0);
	if (c == 'N')
		return (PI / 2);
	if (c == 'W')
		return (PI);
	if (c == 'S')
		return (3 * PI / 2);
	ft_printf(2, "Error during parsing of player's cardinal orientation");
	return (-1);
}
