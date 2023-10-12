/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:03:04 by iaschnei          #+#    #+#             */
/*   Updated: 2023/09/06 12:59:27 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	handle_move_left_y(t_data *data);
static void	handle_move_right_y(t_data *data);

void	handle_move_left(t_data *data)
{
	float	distance;
	float	result;
	float	integral;

	integral = 0;
	get_player_distances_to_wall(data->player, data);
	distance = fmax(0, fmin(data->player->distance_left - HITBOX,
				(float)MOVE_SPEED / (data->fps + 1)));
	result = data->player->dx
		+ distance * cos(angle_sum(data->player->beta, PI / 2));
	if (result < 0)
	{
		data->player->dx = 1 - modff(result, &integral);
		data->player->x -= 1 - (int) integral;
	}
	else if (result > 1)
	{
		data->player->dx = modff(result, &integral);
		data->player->x += (int) integral;
	}
	else
		data->player->dx = result;
	handle_move_left_y(data);
}

static void	handle_move_left_y(t_data *data)
{
	float	distance;
	float	result;
	float	integral;

	integral = 0;
	distance = fmax(0, fmin(data->player->distance_left - HITBOX,
				(float)MOVE_SPEED / (data->fps + 1)));
	result = data->player->dy
		- distance * sin(angle_sum(data->player->beta, PI / 2));
	if (result < 0)
	{
		data->player->dy = 1 - modff(result, &integral);
		data->player->y -= 1 - (int) integral;
	}
	else if (result > 1)
	{
		data->player->dy = modff(result, &integral);
		data->player->y += (int) integral;
	}
	else
		data->player->dy = result;
}

void	handle_move_right(t_data *data)
{
	float	distance;
	float	result;
	float	integral;

	integral = 0;
	get_player_distances_to_wall(data->player, data);
	distance = fmax(0, fmin(data->player->distance_right - HITBOX,
				(float)MOVE_SPEED / (data->fps + 1)));
	result = data->player->dx
		+ distance * cos(angle_sum(data->player->beta, 3 * PI / 2));
	if (result < 0)
	{
		data->player->dx = 1 - modff(result, &integral);
		data->player->x -= 1 - (int) integral;
	}
	else if (result > 1)
	{
		data->player->dx = modff(result, &integral);
		data->player->x += (int) integral;
	}
	else
		data->player->dx = result;
	handle_move_right_y(data);
}

static void	handle_move_right_y(t_data *data)
{
	float	distance;
	float	result;
	float	integral;

	integral = 0;
	distance = fmax(0, fmin(data->player->distance_right - HITBOX,
				(float)MOVE_SPEED / (data->fps + 1)));
	result = data->player->dy
		- distance * sin(angle_sum(data->player->beta, 3 * PI / 2));
	if (result < 0)
	{
		data->player->dy = 1 - modff(result, &integral);
		data->player->y -= 1 - (int) integral;
	}
	else if (result > 1)
	{
		data->player->dy = modff(result, &integral);
		data->player->y += (int) integral;
	}
	else
		data->player->dy = result;
}
