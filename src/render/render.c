/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:06:27 by iaschnei          #+#    #+#             */
/*   Updated: 2023/09/06 11:07:36 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	create_images(t_data *data);
static int	game_state(t_data *data);

// Main render function, creates the window and sets up hooks
void	render(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (data_cleanup(data));
	data->window = mlx_new_window(data->mlx, SCREEN_W, SCREEN_H, "cub3d");
	if (!data->window)
		return (free(data->mlx), data_cleanup(data));
	create_images(data);
	create_keys(data);
	if (!data->keys)
		return (ft_printf(2, "Malloc failed\n"), mlx_cleanup(data));
	mlx_hook(data->window, 17, 0, cross_exit, data);
	mlx_hook(data->window, KeyPress, KeyPressMask, input_press, data);
	mlx_hook(data->window, KeyRelease, KeyReleaseMask, input_release, data);
	mlx_loop_hook(data->mlx, game_state, data);
	mlx_loop(data->mlx);
}

static void	create_images(t_data *data)
{
	data->img = create_image(data, SCREEN_W, SCREEN_H);
	if (!data->img)
		return (mlx_cleanup(data));
	data->minimap = create_image(data, 150, 150);
	if (!data->minimap)
		return (mlx_cleanup(data));
}

// Game loop, called forever by mlx_loop() until game is exited
static int	game_state(t_data *data)
{
	data->old_time = get_time_in_ms();
	movement(data);
	print_default_screen(data);
	print_walls(data);
	print_minimap(data);
	data->time = get_time_in_ms();
	while ((data->time - data->old_time) < 16.67)
	{
		data->time = get_time_in_ms();
		usleep(10);
	}
	mlx_put_image_to_window(data->mlx, data->window, data->img->img_ptr, 0, 0);
	data->fps = calculate_fps(data);
	print_fps(data);
	return (0);
}
