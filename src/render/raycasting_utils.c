/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:29:44 by acostes           #+#    #+#             */
/*   Updated: 2023/09/05 15:32:40 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/// @brief Initializes the variables necessary to
///			compute the raycasting algorithm
/// @param ray
void	set_ray_direction_infos(t_ray *ray)
{
	ray->x = ray->player->x;
	ray->y = ray->player->y;
	ray->theta = angle_sum(ray->player->beta, ray->phi);
	if (ray->theta >= PI / 2 && ray->theta < 3 * PI / 2)
		ray->step_x = -1;
	else
		ray->step_x = 1;
	if (ray->theta >= 0 && ray->theta < PI)
		ray->step_y = -1;
	else
		ray->step_y = 1;
}

/// @brief returns the distance along the ray direction
/// 		between the player and the first vertical border
///			of tile encountered by the ray
/// @return the distance
float	first_vertical_tile_intersect(t_ray *ray)
{
	t_coord	intersect_distance;

	intersect_distance.x = (1 + ray->step_x) / 2 - ray->player->dx;
	intersect_distance.y = intersect_distance.x * tan(ray->theta);
	return (get_norm(intersect_distance));
}

/// @brief returns the distance along the ray direction
/// 		between the player and the first horizontal border
///			of tile encountered by the ray
/// @return the distance
float	first_horizontal_tile_intersect(t_ray *ray)
{
	t_coord	intersect_distance;

	intersect_distance.y = (1 + ray->step_y) / 2 - ray->player->dy;
	intersect_distance.x = intersect_distance.y / tan(ray->theta);
	return (get_norm(intersect_distance));
}

void	cast_ray(t_ray *ray, t_data *data)
{
	while (data->map[ray->y][ray->x] != '1')
	{
		if (ray->t_max_x < ray->t_max_y)
		{
			ray->t_max_x += fabs(1 / cos(ray->theta));
			ray->x += ray->step_x;
			if (ray->step_x == 1)
				ray->wall_orientation = 'W';
			else
				ray->wall_orientation = 'E';
		}
		else
		{
			ray->t_max_y += fabs(1 / sin(ray->theta));
			ray->y += ray->step_y;
			if (ray->step_y == 1)
				ray->wall_orientation = 'N';
			else
				ray->wall_orientation = 'S';
		}
	}
}
