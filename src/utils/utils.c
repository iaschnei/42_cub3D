/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:03:33 by acostes           #+#    #+#             */
/*   Updated: 2023/09/11 13:40:05 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_tab(char **map)
{
	int	i;
	int	j;

	i = 0;
	if (!map)
		return ;
	while (map[i])
		i++;
	j = 0;
	while (j < i)
	{
		free(map[j]);
		j++;
	}
	free(map);
}

void	free_int_tab(int **tab)
{
	int	i;
	int	j;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		i++;
	j = 0;
	while (j < i)
	{
		free(tab[j]);
		j++;
	}
	free(tab);
}

// performs the sum of two angles (assuming both are ∈ [0;2π[)
// making sure the result is ∈ [0;2π[
float	angle_sum(float alpha1, float alpha2)
{
	float	alpha;

	alpha = alpha1 + alpha2;
	if (alpha >= 2 * PI)
		alpha -= 2 * PI;
	else if (alpha < 0)
		alpha += 2 * PI;
	return (alpha);
}

// performs the sum of two sets of coordinates
t_coord	coord_sum(t_coord coord1, t_coord coord2)
{
	t_coord	res;

	res.x = coord1.x + coord2.x;
	res.y = coord1.y + coord2.y;
	return (res);
}
