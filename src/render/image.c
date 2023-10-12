/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 10:25:41 by iaschnei          #+#    #+#             */
/*   Updated: 2023/08/09 13:10:40 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//This creates an imatge struct and initialise every variable of it
//MLX functions here shouldn't be able to fail
t_img	*create_image(t_data *data, int width, int height)
{
	t_img	*ret;

	ret = malloc(sizeof(t_img));
	if (!ret)
		return (NULL);
	ret->img_ptr = mlx_new_image(data->mlx, width, height);
	if (!ret->img_ptr)
		return (NULL);
	ret->address = mlx_get_data_addr(ret->img_ptr, &ret->b_per_pixel,
			&ret->line_length, &ret->endian);
	return (ret);
}

void	ft_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->address + (y * img->line_length + x * (img->b_per_pixel / 8));
	*(unsigned int *)dst = color;
}
