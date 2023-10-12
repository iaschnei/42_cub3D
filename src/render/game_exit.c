/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:22:40 by iaschnei          #+#    #+#             */
/*   Updated: 2023/08/14 14:24:26 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//Exits the game and cleanup everything
void	mlx_cleanup(t_data *data)
{
	mlx_destroy_window(data->mlx, data->window);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img->img_ptr);
	if (data->minimap)
		mlx_destroy_image(data->mlx, data->minimap->img_ptr);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	if (data->img)
		free(data->img);
	if (data->minimap)
		free(data->minimap);
	data_cleanup(data);
	exit(0);
}

int	cross_exit(t_data *data)
{
	mlx_cleanup(data);
	return (0);
}
