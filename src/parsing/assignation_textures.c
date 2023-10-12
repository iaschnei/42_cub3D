/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignation_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:29:11 by acostes           #+#    #+#             */
/*   Updated: 2023/09/11 13:01:33 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*extract_texture(char *line, int begin);

int	assign_textures(char **file, t_textures *textures)
{
	int	iter;
	int	c_iter;

	iter = 0;
	while (file[iter])
	{
		c_iter = 0;
		while (file[iter][c_iter] == ' ')
			c_iter++;
		if (file[iter][c_iter] == 'N' && file[iter][c_iter + 1] == 'O')
			textures->north_text = extract_texture(file[iter], c_iter);
		if (file[iter][c_iter] == 'S' && file[iter][c_iter + 1] == 'O')
			textures->south_text = extract_texture(file[iter], c_iter);
		if (file[iter][c_iter] == 'E' && file[iter][c_iter + 1] == 'A')
			textures->east_text = extract_texture(file[iter], c_iter);
		if (file[iter][c_iter] == 'W' && file[iter][c_iter + 1] == 'E')
			textures->west_text = extract_texture(file[iter], c_iter);
		assign_colors(file, textures, iter, c_iter);
		iter++;
	}
	if (check_malloc(textures))
		return (0);
	return (1);
}

void	assign_colors(char **file, t_textures *textures, int iter, int c_iter)
{
	if (file[iter][c_iter] == 'C' && file[iter][c_iter + 1] == ' ')
		textures->ceil_col = extract_color(file[iter], c_iter);
	if (file[iter][c_iter] == 'F' && file[iter][c_iter + 1] == ' ')
		textures->floor_col = extract_color(file[iter], c_iter);
}

static char	*extract_texture(char *line, int begin)
{
	char	*buffer;
	char	*buffer_trimmed;
	int		iter;

	iter = 0;
	buffer = malloc((ft_strlen(line) - 2 - begin) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (line[iter + 3 + begin] && line[iter + 3 + begin] != '\n')
	{
		buffer[iter] = line[iter + begin + 3];
		iter++;
	}
	buffer[iter] = 0;
	buffer_trimmed = ft_strtrim(buffer, " ");
	free(buffer);
	return (buffer_trimmed);
}

char	*extract_color(char *line, int begin)
{
	char	*buffer;
	char	*buffer_trimmed;
	int		iter;

	iter = 0;
	buffer = malloc((ft_strlen(line) - 1 - begin) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (line[iter + begin + 2] && line[iter + begin + 2] != '\n')
	{
		buffer[iter] = line[iter + begin + 2];
		iter++;
	}
	buffer[iter] = 0;
	buffer_trimmed = ft_strtrim(buffer, " ");
	free(buffer);
	return (buffer_trimmed);
}
