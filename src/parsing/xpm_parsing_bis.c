/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_parsing_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 11:15:34 by iaschnei          #+#    #+#             */
/*   Updated: 2023/09/11 11:25:17 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_height_and_width(t_data *data, char **file_tab);

int	xpm_check(t_data *data, char *file_path, char **file_tab)
{
	size_t	line_i;
	size_t	text_width;

	line_i = 0;
	text_width = find_text_width(file_tab);
	if (ft_strlen(file_path) < 4 || file_path[ft_strlen(file_path) - 1] != 'm'
		|| file_path[ft_strlen(file_path) - 2] != 'p'
		|| file_path[ft_strlen(file_path) - 3] != 'x'
		|| file_path[ft_strlen(file_path) - 4] != '.')
		return (0);
	while (file_tab[line_i] && ft_strlen(file_tab[line_i]) != text_width + 4)
		line_i++;
	while (file_tab[line_i] && file_tab[line_i + 1])
	{
		if (ft_strlen(file_tab[line_i]) != text_width + 4)
			return (0);
		line_i++;
	}
	if (ft_strlen(file_tab[line_i]) != text_width + 5)
		return (0);
	if (!check_height_and_width(data, file_tab))
		return (0);
	return (1);
}

int	extract_code(char c, char **file_tab)
{
	int		iter;
	int		char_iter;

	iter = 0;
	char_iter = 0;
	while (file_tab[iter])
	{
		if (ft_strlen(file_tab[iter]) == 15 && file_tab[iter][1] == c
			&& file_tab[iter][3] == 'c')
		{
			return (ft_atoi_base(file_tab[iter] + 6, "0123456789ABCDEF"));
		}
		iter++;
	}
	return (0);
}

void	free_prev(size_t i, int **tab)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		free(tab[j]);
		j++;
	}
	free(tab);
}

static int	check_height_and_width(t_data *data, char **file_tab)
{
	int	height;
	int	width;

	width = ft_atoi(file_tab[3] + 1);
	if (width <= 0)
		return (0);
	height = ft_atoi(file_tab[3] + 1 + nbr_len(width));
	if (height <= 0)
		return (0);
	if (data->text_height == -1)
		data->text_height = height;
	else if (height != data->text_height)
		return (0);
	if (data->text_width == -1)
		data->text_width = width;
	else if (width != data->text_width)
		return (0);
	return (1);
}
