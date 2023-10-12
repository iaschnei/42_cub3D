/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_default.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:09:33 by iaschnei          #+#    #+#             */
/*   Updated: 2023/08/16 13:18:42 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void		print_floor(t_data *data);
static void		print_ceiling(t_data *data);

void	print_default_screen(t_data *data)
{
	print_floor(data);
	print_ceiling(data);
}

static void	print_floor(t_data *data)
{
	int		color;
	size_t	h_iter;
	size_t	w_iter;

	h_iter = SCREEN_H / 2;
	color = extract_rgb_value(data->textures->floor_col);
	while (h_iter < SCREEN_H)
	{
		w_iter = 0;
		while (w_iter < SCREEN_W)
		{
			ft_pixel_put(data->img, w_iter, h_iter, color);
			w_iter++;
		}
		h_iter++;
	}
}

static void	print_ceiling(t_data *data)
{
	size_t	color;
	size_t	h_iter;
	size_t	w_iter;

	h_iter = 0;
	color = extract_rgb_value(data->textures->ceil_col);
	while (h_iter < SCREEN_H / 2)
	{
		w_iter = 0;
		while (w_iter < SCREEN_W)
		{
			ft_pixel_put(data->img, w_iter, h_iter, color);
			w_iter++;
		}
		h_iter++;
	}
}

size_t	extract_rgb_value(char *line)
{
	int		r;
	int		g;
	int		b;
	size_t	ret;

	r = ft_atoi(line);
	if (r > 255)
		r = 0;
	g = ft_atoi(line + nbr_len(r) + 1);
	if (g > 255)
		g = 0;
	b = ft_atoi(line + nbr_len(r) + nbr_len(g) + 2);
	if (b > 255)
		b = 0;
	ret = (r << 16) + (g << 8) + b;
	return (ret);
}
