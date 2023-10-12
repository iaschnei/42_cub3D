/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:03:04 by iaschnei          #+#    #+#             */
/*   Updated: 2023/09/06 12:59:58 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	handle_move_up(t_data *data);
static void	handle_move_down(t_data *data);
static void	handle_move_up_y(t_data *data);
static void	handle_move_down_y(t_data *data);

int	movement(t_data *data)
{
	if (data->keys->up_pressed == 1)
	{
		handle_move_up(data);
	}
	if (data->keys->down_pressed == 1)
	{
		handle_move_down(data);
	}
	if (data->keys->a_pressed == 1)
	{
		handle_move_left(data);
	}
	if (data->keys->d_pressed == 1)
	{
		handle_move_right(data);
	}
	if (data->keys->left_pressed == 1)
	{
		handle_rot_left(data);
	}
	if (data->keys->right_pressed == 1)
	{
		handle_rot_right(data);
	}
	return (0);
}

static void	handle_move_up(t_data *data)
{
	float	distance;
	float	result;
	float	integral;

	integral = 0;
	get_player_distances_to_wall(data->player, data);
	distance = fmax(0, fmin(data->player->distance_front - HITBOX,
				(float)MOVE_SPEED / (data->fps + 1)));
	result = data->player->dx + distance * cos(data->player->beta);
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
	handle_move_up_y(data);
}

static void	handle_move_up_y(t_data *data)
{
	float	distance;
	float	result;
	float	integral;

	integral = 0;
	distance = fmax(0, fmin(data->player->distance_front - HITBOX,
				(float)MOVE_SPEED / (data->fps + 1)));
	result = data->player->dy - distance * sin(data->player->beta);
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

static void	handle_move_down(t_data *data)
{
	float	distance;
	float	result;
	float	integral;

	integral = 0;
	get_player_distances_to_wall(data->player, data);
	distance = fmax(0, fmin(data->player->distance_back - HITBOX,
				(float)MOVE_SPEED / (data->fps + 1)));
	result = data->player->dx - distance * cos(data->player->beta);
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
	handle_move_down_y(data);
}

static void	handle_move_down_y(t_data *data)
{
	float	distance;
	float	result;
	float	integral;

	integral = 0;
	distance = fmax(0, fmin(data->player->distance_back - HITBOX,
				(float)MOVE_SPEED / (data->fps + 1)));
	result = data->player->dy + distance * sin(data->player->beta);
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
