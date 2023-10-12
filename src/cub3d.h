/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:17:32 by iaschnei          #+#    #+#             */
/*   Updated: 2023/09/11 13:01:45 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define SCREEN_H 900
# define SCREEN_W 1200
# define TILE_WIDTH 1000
# define PI 3.141593
# define MOVE_SPEED 2
# define ROT_SPEED 1.5
# define HITBOX 0.2

# include "../minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "libft/get_next_line_bonus.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <X11/keysym.h>
# include "X11/X.h"
# include <sys/time.h>
# include <math.h>

typedef struct s_keys
{
	int	up_pressed;
	int	down_pressed;
	int	left_pressed;
	int	right_pressed;
	int	d_pressed;
	int	a_pressed;
}	t_keys;

// x -> x position of the player in tile coordinates in map
// y -> y position of the player in tile coordinates in map
// dx -> player relative x position inside the tile (∈ [0;1[)
// dy -> player relative y position inside the tile (∈ [0;1[)
// beta -> orientation of the player in radians relat. to East axis (∈ [0;2π[)
// fov -> field of view amplitude in radians
// distance_front (left, right, back) -> when moving by pressing keys,
//	keep track of the distance the player tries to move in respectively
//	the front, left, right or back direction
typedef struct s_player
{
	int		x;
	int		y;
	float	dx;
	float	dy;
	float	beta;
	float	fov;
	float	distance_front;
	float	distance_left;
	float	distance_right;
	float	distance_back;
}	t_player;

// point or distance represented by its x and y coordinates
typedef struct s_coord
{
	float	x;
	float	y;
}	t_coord;

typedef struct s_vect
{
	float	x;
	float	y;
	float	norm;
	float	angle;
}	t_vect;

// ray relative to a player,
// defined by its angle phi from the player facing direction
// (phi ∈ [-player->fov/2 ; player->fov/2])
// theta -> orientation of the ray in radians relat. to East axis (∈ [0;2π[)
// x -> the x coordinate of the tile the ray is currently traversing
// y -> the y coordinate of the tile the ray is currently traversing
// step_x -> the sign of the direction of the ray in x axis of the map (∈{-1;1})
// step_y -> the sign of the direction of the ray in y axis of the map (∈{-1;1})
// t_max_x -> dist. between player and next vert. border to be reached by ray
// t_max_y -> dist. between player and next horiz. border to be reached by ray
// wall_orientation -> the cardinal direction the wall hit by the ray is facing
typedef struct s_ray
{
	t_player	*player;
	float		phi;
	float		theta;
	int			x;
	int			y;
	int			step_x;
	int			step_y;
	float		t_max_x;
	float		t_max_y;
	char		wall_orientation;
}	t_ray;

// xxx_text -> path to the texture of xxx orientation
// xxx_col -> color of the ceiling or floor (char * like that : "int,int,int")
typedef struct s_textures
{
	char	*north_text;
	int		**north_tab;
	char	*south_text;
	int		**south_tab;
	char	*west_text;
	int		**west_tab;
	char	*east_text;
	int		**east_tab;
	char	*floor_col;
	char	*ceil_col;
}	t_textures;

//This holds the data necessary for an image
//	'img_ptr' == the pointer returned by mlx_new_image(...)
//	'address' == the address returned by mlx_get_data_addr(...)
//	'b_per_pixel' == bits per pixel or color depth (determined by mlx)
//!	'line_length' == length of a line, but not necessarily == SCREEN_WIDTH
//	'endian' == a way of storing memory for the computer (determined by mlx)
typedef struct s_img
{
	void	*img_ptr;
	char	*address;
	int		b_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_data
{
	size_t		time;
	size_t		old_time;
	size_t		fps;
	int			text_width;
	int			text_height;
	t_player	*player;
	int			*wall_heights;
	float		*wall_intersects;
	char		*wall_orientations;
	t_textures	*textures;
	char		**map;
	void		*mlx;
	void		*window;
	t_img		*img;
	t_img		*minimap;
	t_keys		*keys;
}	t_data;

// ------- CLEAN -------
void	data_cleanup(t_data *data);
void	mlx_cleanup(t_data *data);

// ------- UTILS -------
void	free_tab(char **map);
void	free_prev(size_t i, int **tab);
void	free_int_tab(int **tab);
float	angle_sum(float alpha1, float alpha2);
float	get_norm(t_coord coord);
int		ft_atoi_base(char *str, char *base);

// ------- PARSING -------
int		parsing(int ac, char **av, t_data *data);
int		is_text_identifier(char **map, int line, int c_i);
char	**from_list_to_arr(t_list *map_list);;
char	**incorrect_map_file(char **av);
int		check_text_lines(char **map);
int		check_map_lines(char **map);
void	fill_buffer(char *buffer, char *line, int begin, int iter);
int		find_first_line(char **map);
int		assign_data(char **file, t_data *data);
int		assign_textures(char **file, t_textures *textures);
int		check_malloc(t_textures *tex);
int		check_useless_lines(char **map);
char	**extract_map(char **file);
void	initialise_text(t_textures *tex);
int		check_max_colors(char *line);
float	get_spawn_beta(char c);
int		find_last_line(char **map, int iter);
size_t	extract_rgb_value(char *line);
char	*extract_color(char *line, int begin);
void	extract_textures(t_data *data);
int		extract_code(char c, char **file_tab);
int		**make_color_tab(t_data *data, char *file_path);
size_t	find_text_width(char **file_tab);
int		xpm_check(t_data *data, char *file_path, char **file_tab);
int		check_around_zeros(char **map, int i);
void	assign_colors(char **file, t_textures *textures, int iter, int c_iter);

// ------- RENDER -------
void	render(t_data	*data);
t_img	*create_image(t_data *data, int width, int height);
void	ft_pixel_put(t_img *img, int x, int y, int color);
void	print_default_screen(t_data *data);
size_t	get_time_in_ms(void);
size_t	calculate_fps(t_data *data);
void	print_fps(t_data *data);
void	print_walls(t_data *data);
void	print_minimap(t_data *data);
void	print_visionray(t_data *data);
void	set_ray_direction_infos(t_ray *ray);
float	first_vertical_tile_intersect(t_ray *ray);
float	first_horizontal_tile_intersect(t_ray *ray);
void	cast_ray(t_ray *ray, t_data *data);
float	get_distance_to_wall(t_ray *ray, int i, t_data *data);
void	generate_wall_heights(t_data *data);
void	get_player_distances_to_wall(t_player *player, t_data *data);

// ------- INPUT --------
void	create_keys(t_data *data);
int		cross_exit(t_data *data);
int		input_press(int key, t_data *data);
int		movement(t_data *data);
void	handle_move_left(t_data *data);
void	handle_move_right(t_data *data);
int		input_release(int key, t_data *data);
void	handle_rot_left(t_data *data);
void	handle_rot_right(t_data *data);

#endif
