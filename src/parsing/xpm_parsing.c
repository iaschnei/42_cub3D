/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:15:56 by iaschnei          #+#    #+#             */
/*   Updated: 2023/09/11 11:26:07 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char		**make_file_tab(char *file_path);
static size_t	find_alloc_size(char **file_tab);
static void		fill_color_tab(char **file_tab, int	**color_tab);

int	**make_color_tab(t_data *data, char *file_path)
{
	char	**file_tab;
	size_t	i;
	int		**color_tab;
	size_t	alloc_size;

	file_tab = make_file_tab(file_path);
	if (!file_tab)
		return (NULL);
	i = 0;
	if (!xpm_check(data, file_path, file_tab))
		return (free_tab(file_tab), NULL);
	alloc_size = find_alloc_size(file_tab);
	color_tab = malloc((alloc_size + 1) * sizeof (int *));
	if (!color_tab)
		return (free_tab(file_tab), NULL);
	while (i < alloc_size)
	{
		color_tab[i] = malloc((find_text_width(file_tab) + 1) * sizeof(int));
		if (!color_tab[i])
			return (free_tab(file_tab), free_prev(i, color_tab), NULL);
		i++;
	}
	color_tab[alloc_size] = 0;
	fill_color_tab(file_tab, color_tab);
	return (free_tab(file_tab), color_tab);
}

static char	**make_file_tab(char *file_path)
{
	int		fd;
	t_list	*file_list;
	char	*current_line;
	char	**ret;

	file_list = NULL;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	current_line = get_next_line(fd);
	while (current_line)
	{
		ft_lstadd_back(&file_list, ft_lstnew(ft_strdup(current_line)));
		free(current_line);
		current_line = get_next_line(fd);
	}
	close(fd);
	if (!file_list || ft_lstsize(file_list) < 8)
		return (ft_lstclear(&file_list, free), NULL);
	ret = from_list_to_arr(file_list);
	ft_lstclear(&file_list, free);
	if (!ret)
		return (NULL);
	return (ret);
}

static size_t	find_alloc_size(char **file_tab)
{
	size_t	ret;
	int		iter;
	size_t	text_width;

	ret = 1;
	iter = 0;
	text_width = find_text_width(file_tab);
	while (file_tab[iter] && ft_strlen(file_tab[iter]) != text_width + 4)
		iter++;
	while (file_tab[iter] && ft_strlen(file_tab[iter]) == text_width + 4)
	{
		ret++;
		iter++;
	}
	return (ret);
}

size_t	find_text_width(char **file_tab)
{
	int		iter;
	size_t	text_width;

	iter = 0;
	text_width = 0;
	while (file_tab[iter])
	{
		if (iter >= 2 && ft_strlen(file_tab[iter]) >= 9
			&& file_tab[iter][0] == '"')
		{
			text_width = ft_atoi(file_tab[iter] + 1);
			break ;
		}
		iter++;
	}
	return (text_width);
}

static void	fill_color_tab(char **file_tab, int **color_tab)
{
	size_t	text_width;
	int		line_i;
	size_t	char_i;
	int		color_i;
	size_t	code_i;

	line_i = 0;
	color_i = 0;
	text_width = find_text_width(file_tab);
	while (file_tab[line_i] && ft_strlen(file_tab[line_i]) != text_width + 4)
		line_i++;
	while (file_tab[line_i] && ft_strlen(file_tab[line_i]) >= text_width + 2)
	{
		char_i = 1;
		code_i = 0;
		while (file_tab[line_i][char_i] && file_tab[line_i][char_i] != '"')
		{
			color_tab[color_i][code_i] = extract_code(file_tab[line_i][char_i],
					file_tab);
			char_i++;
			code_i++;
		}
		color_i++;
		line_i++;
	}
}
