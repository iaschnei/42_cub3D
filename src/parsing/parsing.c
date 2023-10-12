/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:24:45 by iaschnei          #+#    #+#             */
/*   Updated: 2023/09/06 13:48:46 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	incorrect_num_of_arg(int ac);
static int	incorrect_map_path(char **av);
static int	print_error(char *s);
static int	print_map_error(void);

//Check number of args first, then correctness of the path to the file
//Then the file itself, and if everything is correct, assign to data
int	parsing(int ac, char **av, t_data *data)
{
	char	**file;

	if (incorrect_num_of_arg(ac))
		return (free(data), 0);
	else if (incorrect_map_path(av))
		return (free(data), 0);
	file = incorrect_map_file(av);
	if (!file)
		return (data_cleanup(data), print_map_error());
	if (!assign_data(file, data))
		return (data_cleanup(data), printf("Malloc error\n"), 1);
	return (1);
}

// Checks that the user does input only one argument
static int	incorrect_num_of_arg(int ac)
{
	if (ac != 2)
	{
		printf("Error\nIncorrect number of arguments.\n");
		printf("Please input a path to a .cub map.\n");
		return (1);
	}
	return (0);
}

// Checks that the map path is correct and leads to a file
// 	-Length at least 5 (* + .cub)
// 	-Ends with .cub
// 	-Can be opened and read
static int	incorrect_map_path(char **av)
{
	int	iter;
	int	fd;

	iter = 0;
	while (av[1][iter])
		iter++;
	if (iter < 5)
		return (print_error(NULL));
	else if (av[1][iter - 1] != 'b' || av[1][iter - 2] != 'u'
			|| av[1][iter - 3] != 'c' || av[1][iter - 4] != '.')
		return (print_error(NULL));
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (print_error(av[1]));
	if (read(fd, NULL, 0) == -1)
	{
		close(fd);
		return (print_error(av[1]));
	}
	close(fd);
	return (0);
}

// Print errors in case the map path is invalid
// If a path is provided, specify it in the error message
static int	print_error(char *s)
{
	if (!s)
	{
		printf("Error\nInvalid map path.\n");
		printf("Please input a path to a .cub map.\n");
		return (1);
	}
	else
	{
		printf("Error\n'%s' isn't pointing to a valid file.\n", s);
		printf("Please input a path to a .cub map.\n");
		return (1);
	}
}

static int	print_map_error(void)
{
	printf("Error\nInvalid file configuration.\n");
	printf("Please review the map file and textures paths.\n");
	return (0);
}
