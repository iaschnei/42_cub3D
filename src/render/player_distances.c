/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_distances.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:52:53 by acostes           #+#    #+#             */
/*   Updated: 2023/09/06 11:15:29 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/// @brief records in player structure:
///			- distance_front: distance between the player and the first wall
///				in player's lookup direction
///			- distance_back: distance between the player and the first wall
///				in player's opposite lookup direction
void	get_player_distances_to_wall(t_player *player, t_data *data)
{
	t_ray	ray;

	ray.player = player;
	ray.phi = 0;
	set_ray_direction_infos(&ray);
	player->distance_front = get_distance_to_wall(&ray, -1, data);
	ray.phi = PI / 2;
	set_ray_direction_infos(&ray);
	player->distance_left = get_distance_to_wall(&ray, -1, data);
	ray.phi = PI;
	set_ray_direction_infos(&ray);
	player->distance_back = get_distance_to_wall(&ray, -1, data);
	ray.phi = 3 * PI / 2;
	set_ray_direction_infos(&ray);
	player->distance_right = get_distance_to_wall(&ray, -1, data);
}
