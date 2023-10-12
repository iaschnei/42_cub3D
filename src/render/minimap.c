/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:36:37 by iaschnei          #+#    #+#             */
/*   Updated: 2023/09/11 10:56:00 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	print_background(t_data *data, t_img *minimap);
static void	find_walls(t_data *data, t_img *minimap, int x, int y);
static void	print_wall_mini(int x, int y, t_img *minimap);

void	print_minimap(t_data *data)
{
	print_background(data, data->img);
	find_walls(data, data->img, data->player->x, data->player->y);
	print_visionray(data);
}

static void	print_background(t_data *data, t_img *minimap)
{
	int	i;
	int	j;

	i = 0;
	while (i < 150)
	{
		j = 0;
		while (j < 150)
		{
			if ((i % 30 == 0 || j % 30 == 0) || (i == 149 || j == 149))
				ft_pixel_put(minimap, j + SCREEN_W - 165, i + 15, 0x000000);
			else if ((i > 71 + 15 * (data->player->dy - 0.5)
					&& i < 79 + 15 * (data->player->dy - 0.5))
				&& (j > 71 + 15 * (data->player->dx - 0.5)
					&& j < 79 + 15 * (data->player->dx - 0.5)))
				ft_pixel_put(minimap, j + SCREEN_W - 165, i + 15, 0xF44A4A);
			else
				ft_pixel_put(minimap, j + SCREEN_W - 165, i + 15, 0xCCCCCC);
			j++;
		}
		i++;
	}
}

static void	find_walls(t_data *data, t_img *minimap, int x, int y)
{
	int	i;
	int	j;

	i = -2;
	while (i < 3)
	{
		j = -2;
		while (j < 3)
		{
			if (y + i < 0 || x + j < 0 || !data->map[y + i]
				|| ft_strlen(data->map[y + i]) < (size_t)(x + j)
				|| !data->map[y + i][x + j]
				|| data->map[y + i][x + j] == '1'
				|| data->map[y + i][x + j] == ' '
				|| data->map[y + i][x + j] == '\n')
				print_wall_mini(j, i, minimap);
			j++;
		}
		i++;
	}
}

static void	print_wall_mini(int x, int y, t_img *minimap)
{
	int	x_tmp;
	int	y_tmp;

	x = (x + 2) * 30;
	y = (y + 2) * 30;
	x_tmp = x;
	y_tmp = y;
	while (x < x_tmp + 30)
	{
		y = y_tmp;
		while (y < y_tmp + 30)
		{
			ft_pixel_put(minimap, x + SCREEN_W - 165, y + 15, 0x413F3F);
			y++;
		}
		x++;
	}
}

void	print_visionray(t_data *data)
{
	int	i;
	int	j;
	int	k;

	k = 15;
	i = (int)((75 + SCREEN_W - 165) + k * cos(data->player->beta));
	while (k < 75)
	{
		i = (int)((75 + SCREEN_W - 165) + k * cos(data->player->beta));
		j = (int)((75 + 15) - k * sin(data->player->beta));
		ft_pixel_put(data->img, i, j, 0xF44A4A);
		k++;
	}
}
