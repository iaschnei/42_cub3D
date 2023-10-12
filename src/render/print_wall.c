/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:28:14 by iaschnei          #+#    #+#             */
/*   Updated: 2023/09/06 13:33:12 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	print_pixel_column(t_data *data, int column, int height,
				int **tab);

/// @brief draw the walls for every column of pixels of the screen
void	print_walls(t_data *data)
{
	int	iter;
	int	h;

	iter = 0;
	generate_wall_heights(data);
	while (data->wall_heights[iter])
	{
		h = data->wall_heights[iter];
		if (data->wall_orientations[iter] == 'N')
			print_pixel_column(data, iter, h, data->textures->north_tab);
		if (data->wall_orientations[iter] == 'S')
			print_pixel_column(data, iter, h, data->textures->south_tab);
		if (data->wall_orientations[iter] == 'E')
			print_pixel_column(data, iter, h, data->textures->east_tab);
		if (data->wall_orientations[iter] == 'W')
			print_pixel_column(data, iter, h, data->textures->west_tab);
		iter++;
	}
}

/// @brief variation of ft_pixel_put
///			narrowing the vertical range of pixels to [0, SCREEN_H[
///			(to avoid segfaults when the wall is so close it does not fit
///			entirely on the screen height)
static void	my_pixel_put(t_img *img, int x, int y, int color)
{
	if (y < 0 || y >= SCREEN_H)
		y = SCREEN_H - 1;
	ft_pixel_put(img, x, y, color);
}

/// @brief for every pixel of a pixel column,
///			access the corresponding color
///			extracted from the appropriate texture file
static void	print_pixel_column(t_data *data, int column, int height,
	int	**tab)
{
	int	iter;
	int	color;
	int	y;

	iter = 0;
	if (data->wall_orientations[column] == 'W')
		color = 2829634;
	else if (data->wall_orientations[column] == 'E')
		color = 9279918;
	else if (data->wall_orientations[column] == 'N')
		color = 15594228;
	else if (data->wall_orientations[column] == 'S')
		color = 8419710;
	while (iter < height)
	{
		if (tab && tab[iter * (data->text_height - 1) / height]
			[(int)(data->wall_intersects[column] * (data->text_width - 1))]
			!= -1)
			color = tab[iter * (data->text_height - 1) / height]
			[(int)(data->wall_intersects[column] * (data->text_width - 1))];
		y = iter + SCREEN_H / 2 - height / 2;
		my_pixel_put(data->img, column, y, color);
		iter++;
	}
}
