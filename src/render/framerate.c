/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   framerate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:01:02 by iaschnei          #+#    #+#             */
/*   Updated: 2023/08/14 14:10:09 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	get_time_in_ms(void)
{
	struct timeval	time_struct;
	size_t			ret;

	gettimeofday(&time_struct, NULL);
	ret = time_struct.tv_sec * 1000 + time_struct.tv_usec / 1000;
	return (ret);
}

size_t	calculate_fps(t_data *data)
{
	size_t	diff;

	diff = 1000 / (data->time - data->old_time);
	return (diff);
}

void	print_fps(t_data *data)
{
	char	*join_str;
	char	*fps_str;

	fps_str = ft_itoa(data->fps);
	if (!fps_str)
		mlx_string_put(data->mlx, data->window, 10, 15, 0xFFFFFF,
			"FPS: malloc error");
	else
	{
		join_str = ft_strjoin("FPS: ", fps_str);
		if (!join_str)
			mlx_string_put(data->mlx, data->window, 10, 15, 0xFFFFFF,
				"FPS: malloc error");
		else
		{
			mlx_string_put(data->mlx, data->window, 10, 15, 0xFFFFFF, join_str);
			free(join_str);
		}
		free(fps_str);
	}
}
