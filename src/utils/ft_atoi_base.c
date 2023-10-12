/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 21:46:06 by acostes           #+#    #+#             */
/*   Updated: 2023/09/05 16:37:42 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_char_duplicated(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		if (count > 1)
			return (1);
		i++;
	}
	return (0);
}

static int	is_base_valid(char *base)
{
	int	i;

	if (ft_strlen(base) <= 1)
		return (0);
	i = 0;
	while (base[i])
	{
		if (is_char_duplicated(base, base[i]))
			return (0);
		if (base[i] == '+' || base[i] == '-')
			return (0);
		if (base[i] == ' ' || (base[i] >= '\t' && base[i] <= '\r'))
			return (0);
		i++;
	}
	return (1);
}

static int	find_base_index(char *base, char c)
{
	int	i;
	int	base_size;

	i = 0;
	base_size = ft_strlen(base);
	while (i < base_size)
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	int	nb;
	int	i;
	int	count_minus;

	if (is_base_valid(base))
	{
		i = 0;
		while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
			i++;
		count_minus = 0;
		while (str[i] == '-' || str[i] == '+')
		{
			if (str[i] == '-')
				count_minus++;
			i++;
		}
		nb = 0;
		while (find_base_index(base, str[i]) != -1)
			nb = nb * ft_strlen(base) + find_base_index(base, str[i++]);
		if (count_minus % 2 == 1)
			nb = -nb;
		return (nb);
	}
	return (-1);
}
