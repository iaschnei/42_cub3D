/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:58:02 by acostes           #+#    #+#             */
/*   Updated: 2023/08/16 11:59:55 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/// @brief return the vector w obtained by summing
///			the 2 vectors u and v in parameters
/// @return w
t_vect	vect_sum(t_vect u, t_vect v)
{
	t_vect	w;

	w.x = u.x + v.x;
	w.y = u.y + v.y;
	w.norm = sqrt(u.norm * u.norm + v.norm * v.norm);
	u.angle = acos((u.x * v.x + u.y * v.y) / (u.norm * v.norm));
	return (w);
}
