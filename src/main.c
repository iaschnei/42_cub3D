/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:58:14 by iaschnei          #+#    #+#             */
/*   Updated: 2023/09/05 18:03:04 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
! INSTALLER "Better Comments" pour avoir la syntaxe dans les commentaires
*/

static void	data_init(t_data *data);
static void	data_pre_cleanup(t_data *data);

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_printf(2, "malloc error\n"), 1);
	data_init(data);
	if (!parsing(ac, av, data))
		return (1);
	render(data);
	return (0);
}

static void	data_init(t_data *data)
{
	data->img = NULL;
	data->minimap = NULL;
	data->player = NULL;
	data->textures = NULL;
	data->map = NULL;
	data->old_time = 0;
	data->time = 0;
	data->text_height = -1;
	data->text_width = -1;
	data->keys = NULL;
	data->wall_heights = NULL;
	data->wall_intersects = NULL;
	data->wall_orientations = NULL;
}

static void	data_pre_cleanup(t_data *data)
{
	if (data->textures->north_tab)
		free_int_tab(data->textures->north_tab);
	if (data->textures->south_tab)
		free_int_tab(data->textures->south_tab);
	if (data->textures->east_tab)
		free_int_tab(data->textures->east_tab);
	if (data->textures->west_tab)
		free_int_tab(data->textures->west_tab);
}

void	data_cleanup(t_data *data)
{
	if (data->textures)
		data_pre_cleanup(data);
	if (data->textures)
	{
		free(data->textures->north_text);
		free(data->textures->south_text);
		free(data->textures->east_text);
		free(data->textures->west_text);
		free(data->textures->floor_col);
		free(data->textures->ceil_col);
		free(data->textures);
	}
	if (data->map)
		free_tab(data->map);
	if (data->keys)
		free(data->keys);
	if (data->wall_heights)
		free(data->wall_heights);
	if (data->wall_intersects)
		free(data->wall_intersects);
	if (data->wall_orientations)
		free(data->wall_orientations);
	free(data->player);
	free(data);
}
