/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:15:21 by iaschnei          #+#    #+#             */
/*   Updated: 2023/09/06 13:32:51 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_player_distances(t_player *player);
static void	assign_player(char **file, t_player *player);
static int	assign_data_bis(t_data *data);

int	assign_data(char **file, t_data *data)
{
	t_player	*player;
	t_textures	*textures;

	player = malloc(sizeof(t_player));
	if (!player)
		return (free_tab(file), 0);
	textures = malloc(sizeof(t_textures));
	if (!textures)
		return (free(player), free_tab(file), 0);
	initialise_text(textures);
	assign_player(file, player);
	if (!assign_textures(file, textures))
		return (free(player), free(textures), free_tab(file), 0);
	data->player = player;
	data->textures = textures;
	data->map = (extract_map(file));
	free_tab(file);
	if (!data->map)
		return (free(player), free(textures), 0);
	if (!assign_data_bis(data))
		return (0);
	return (1);
}

static int	assign_data_bis(t_data *data)
{
	data->wall_heights = malloc((SCREEN_W + 1) * sizeof(int));
	if (!data->wall_heights)
		return (data_cleanup(data), 0);
	data->wall_intersects = malloc((SCREEN_W + 1) * sizeof(int));
	if (!data->wall_intersects)
		return (data_cleanup(data), 0);
	data->wall_orientations = malloc((SCREEN_W + 1) * sizeof(char));
	if (!data->wall_orientations)
		return (data_cleanup(data), 0);
	data->textures->north_tab = make_color_tab(data,
			data->textures->north_text);
	if (!data->textures->north_tab)
		printf("Error in parsing:\nUsing default texture for north.\n");
	data->textures->south_tab = make_color_tab(data,
			data->textures->south_text);
	if (!data->textures->south_tab)
		printf("Error in parsing:\nUsing default texture for south.\n");
	data->textures->east_tab = make_color_tab(data, data->textures->east_text);
	if (!data->textures->east_tab)
		printf("Error in parsing:\nUsing default texture for east.\n");
	data->textures->west_tab = make_color_tab(data, data->textures->west_text);
	if (!data->textures->west_tab)
		printf("Error in parsing:\nUsing default texture for west.\n");
	return (1);
}

// Fill the player struct :
// Find the player starting position starting from the first line of the map
static void	assign_player(char **file, t_player *player)
{
	int	iter;
	int	c_iter;

	iter = find_first_line(file);
	while (file[iter])
	{
		c_iter = -1;
		while (file[iter][++c_iter])
		{
			if (file[iter][c_iter] == 'N' || file[iter][c_iter] == 'S'
				|| file[iter][c_iter] == 'E' || file[iter][c_iter] == 'W')
			{
				player->beta = get_spawn_beta(file[iter][c_iter]);
				player->fov = PI / 3;
				player->y = iter - find_first_line(file);
				player->x = c_iter;
				player->dy = 0.5;
				player->dx = 0.5;
				init_player_distances(player);
				return ;
			}
		}
		iter++;
	}
}

static void	init_player_distances(t_player *player)
{
	player->distance_front = 0;
	player->distance_left = 0;
	player->distance_right = 0;
	player->distance_back = 0;
}
