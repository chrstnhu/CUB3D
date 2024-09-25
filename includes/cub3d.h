/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:30:47 by chrhu             #+#    #+#             */
/*   Updated: 2024/09/23 12:40:55 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define DEF "\033[0;39m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define YELLOW "\033[0;33m"

# define WIN_WIDTH 960
# define WIN_HEIGHT 720

# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h> //for open
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

enum	e_texture_index
{
	NO = 0,
	SO = 1,
	EA = 2,
	WE = 3,
};

enum	e_hit_side{
	HIT_SIDE_X = 0,
	HIT_SIDE_Y = 1
};

typedef struct s_img
{
	void			*mlx_img;
	int				*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_img;

typedef struct s_texinfo
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			**rgb_parts;
	int				*floor;
	int				*ceiling;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	int				size;
	int				index;
	double			step;
	double			pos;
	int				x;
	int				y;
}					t_texinfo;

typedef struct s_wholemap
{
	int				fd;
	int				line_count;
	char			*path;
	char			**file;
	int				height;
	int				width;
	int				index_end_of_map;
}					t_wholemap;

typedef struct s_player
{
	char			dir;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	int				has_moved;
	int				move_x;
	int				move_y;
	int				rotate;

}					t_player;

typedef struct s_ray
{
	double			camera_plane_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_grid_x;
	int				map_grid_y;
	int				step_x;
	int				step_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				hit_side;
	double			wall_x;
	int				wall_line_height;
	int				draw_start;
	int				draw_end;
}					t_ray;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	int				win_height;
	int				win_width;
	int				player_count;
	int				collision;
	t_wholemap		wholemap;
	char			**map;
	t_player		player;
	t_ray			ray;
	int				**texture_pixels;
	int				**textures;
	t_texinfo		texinfo;
	t_img			playermap;
}					t_data;

typedef struct s_map_elements
{
	int				north;
	int				south;
	int				west;
	int				east;
	int				floor;
	int				ceiling;
}				t_map_elements;

// Check cub file
int					file_valid(char *file);
int					check_cub_file(char *path);
int					check_texture(char *line, t_map_elements *elements);
int					validate_map(t_map_elements *elements);
int					process_line(char *line, t_map_elements *elements);

// Check cub utils
int					check_texture_path(char **line, int *element_flag);
int					check_color_element(char **line, int *element_flag);
int					path_valid(char *path);
// Check border map
int					check_border_walls(t_data *data, char **map);
// Check rgb color
int					check_digit(char *line);
int					check_color(char *line);
char				**split_color(char *line);
// Check map (invalid charactere, player)
int					check_map(t_data *data);

// Utils
void				jump_space(char **line);
void				free_tab(void **tab);
void				trim(char **str);
char				*clean_spaces(const char *line);
void				init_map_element(t_map_elements *elements);

// Error
int					error_msg(char *str, int error);
void				clean_exit(t_data *data, char *error_message, int code);
void				free_texture(char **texture);
void				free_texinfo(t_texinfo *texinfo);
void				free_map(char **map);
void				free_textures(void **textures, int count);
int					error_exit(char *s);

// Parsing
int					count_map_lines(t_data *data, char **map, int i);
int					fill_map_tab(t_wholemap *wholemap, char **map_tab,
						int start);
int					parse_map(t_data *data, char **map);
int					parse_texture(t_texinfo *texinfo, char *line);
int					parse_color(t_texinfo *texinfo, int *color, char *line);
int					parse_line(t_data *data, char *line);
int					parse_cub_file(t_data *data, char *path);

// Initialize Data
void				init_data(t_data *data);
// Initialize Texture
void				init_ray(t_ray *ray);
void				init_textures(t_data *data);
void				init_texture_pix(t_data *data);
// Initialize Minilibx
void				init_mlx(t_data *data);
void				init_img(t_data *data, t_img *image, int width, int height);
void				init_img_clean(t_img *img);
// Initialize Player
void				init_player_west_east(t_player *player);
void				init_player_north_south(t_player *player);

// main.c

// render.c
void				render_screen(t_data *data);
void				update_texture_pix(t_data *data, t_texinfo *tex, t_ray *ray,
						int x);
void				render_frame(t_data *data);
int					close_win(t_data *data);
int					key_press(int keysym, t_data *data);
int					key_release(int keysym, t_data *data);

// Raycasting
int					raycasting(t_data *data);
void				calc_delta_dist(t_data *data, int x);
void				calc_side_dist(t_data *data);
void				dda(t_data *data, t_ray *ray);
void				calculate_line_height(t_data *data, t_ray *ray);

// Player
int					player_move(t_data *data);
int					validate_move(t_data *data, double x, double y);
int					rotate_player(t_data *data, double rotate_dir);

// BONUS
int					validate_move_bonus(t_data *data, double x, double y);
int					mouse_motion(int new_x, int y, t_data *data);
#endif
