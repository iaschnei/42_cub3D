/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:29:13 by iaschnei          #+#    #+#             */
/*   Updated: 2023/09/06 11:31:01 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	create_keys(t_data *data)
{
	data->keys = malloc(sizeof(t_keys));
	if (!data->keys)
		return ;
	data->keys->down_pressed = 0;
	data->keys->up_pressed = 0;
	data->keys->left_pressed = 0;
	data->keys->right_pressed = 0;
	data->keys->d_pressed = 0;
	data->keys->a_pressed = 0;
}

int	input_press(int key, t_data *data)
{
	if (key == XK_Escape)
		mlx_cleanup(data);
	else if (key == XK_Up || key == XK_w)
		data->keys->up_pressed = 1;
	else if (key == XK_Down || key == XK_s)
		data->keys->down_pressed = 1;
	else if (key == XK_Left)
		data->keys->left_pressed = 1;
	else if (key == XK_Right)
		data->keys->right_pressed = 1;
	else if (key == XK_a)
		data->keys->a_pressed = 1;
	else if (key == XK_d)
		data->keys->d_pressed = 1;
	return (0);
}

int	input_release(int key, t_data *data)
{
	if (key == XK_Up || key == XK_w)
		data->keys->up_pressed = 0;
	else if (key == XK_Down || key == XK_s)
		data->keys->down_pressed = 0;
	else if (key == XK_Left)
		data->keys->left_pressed = 0;
	else if (key == XK_Right)
		data->keys->right_pressed = 0;
	else if (key == XK_a)
		data->keys->a_pressed = 0;
	else if (key == XK_d)
		data->keys->d_pressed = 0;
	return (0);
}
