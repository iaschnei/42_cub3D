/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:12:51 by acostes           #+#    #+#             */
/*   Updated: 2023/09/06 13:22:03 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/// @brief returns the distance between the player and the first wall
///			encountered by the ray
///			(corresponding to the ith pixels column on the screen)
///			principle of the algorithm:
///				http://www.cse.yorku.ca/~amana/research/grid.pdf
///			Also calculates the horizontal portion of the wall ∈ [0 ; 1[
///			where the ray hit, then stored in the data->wall_intersects array
///			(to determine what column of the texture file to display)
/// @return distance player / first wall in ray direction
float	get_distance_to_wall(t_ray *ray, int i, t_data *data)
{
	float	d;
	float	projected_d;

	ray->t_max_x = first_vertical_tile_intersect(ray);
	ray->t_max_y = first_horizontal_tile_intersect(ray);
	cast_ray(ray, data);
	if (ray->wall_orientation == 'W' || ray->wall_orientation == 'E')
	{
		d = ray->t_max_x - fabs(1 / cos(ray->theta));
		projected_d = d * sin(ray->theta) - ray->player->dy;
		if (i != -1)
			data->wall_intersects[i] = projected_d - floorf(projected_d);
		return (d);
	}
	else
	{
		d = ray->t_max_y - fabs(1 / sin(ray->theta));
		projected_d = d * cos(ray->theta) + ray->player->dx;
		if (i != -1)
			data->wall_intersects[i] = projected_d - floorf(projected_d);
		return (d);
	}
}

/// @brief returns the distance between the player and the first wall
///			encountered by the ray, projected in player's lookup direction
/// @return distance player / first wall projected in player's lookup direction
static float	get_projected_distance_to_wall(t_ray *ray, int i, t_data *data)
{
	float	d;

	d = get_distance_to_wall(ray, i, data);
	return (d * cos(ray->phi));
}

/// @brief calculates the "height" of the first wall hit by the ray
///			(the number of pixels necessary
///			to draw the entire height of the wall, note that it can be
///			superior to the vertical resolution of the screen,
///			although we limit it with a safety factor to avoid too
///			complex calculations making the fps drop).
static int	get_wall_height(t_ray *ray, int i, t_data *data)
{
	float	p;
	float	h;

	p = get_projected_distance_to_wall(ray, i, data);
	h = SCREEN_H / (2 * tan(ray->player->fov / 2) * p);
	if (h >= 15 * SCREEN_H)
		h = 15 * SCREEN_H;
	return ((int) h);
}

/// @brief for every pixel column on the screen,
///			cast a ray of the player's field of view (fov)
///			and determines the "height" of the wall
///			(the number of pixels necessary
///			to draw the entire height of the wall, note that it can be
///			superior to the vertical resolution of the screen).
///			All heights are then stored in the data->wall_heights array
void	generate_wall_heights(t_data *data)
{
	t_ray	ray;
	int		column;

	ray.player = data->player;
	column = 0;
	ray.phi = +ray.player->fov / 2;
	while (column < SCREEN_W)
	{
		set_ray_direction_infos(&ray);
		data->wall_heights[column] = get_wall_height(&ray, column, data);
		data->wall_orientations[column] = ray.wall_orientation;
		ray.phi -= ray.player->fov / SCREEN_W;
		column++;
	}
	data->wall_heights[column] = 0;
}
