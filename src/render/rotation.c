/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:12:59 by iaschnei          #+#    #+#             */
/*   Updated: 2023/08/17 13:13:21 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	handle_rot_left(t_data *data)
{
	float	rotation;

	rotation = (float)ROT_SPEED / data->fps;
	data->player->beta = angle_sum(data->player->beta, rotation);
}

void	handle_rot_right(t_data *data)
{
	float	rotation;

	rotation = (float)ROT_SPEED / data->fps;
	data->player->beta = angle_sum(data->player->beta, -rotation);
}
