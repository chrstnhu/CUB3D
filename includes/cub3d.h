/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:30:47 by chrhu             #+#    #+#             */
/*   Updated: 2024/08/14 19:29:10 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define DEF "\033[0;39m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"

#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h> //for open
#include "../minilibx-linux/mlx.h"
#include "../libft/includes/libft.h"


typedef struct s_img
{
	void *mlx_img;
	char *addr;
	int bpp;
	int line_len;
	int endian;
}		t_img;

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
}	t_texinfo;

typedef struct s_wholemap
{
	int			fd;
	int			line_count;
	char		*path;
	char		**file;
	int			height;
	int			width;
	int			index_end_of_map;
}	t_wholemap;

typedef struct s_player
{
	char	dir;
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
	int		has_moved;
	int		move_x;
	int		move_y;
	int		rotate;

}			t_player;


typedef struct s_playermap
{
	char	**map;
	t_img	*img;
	int		size;
	int		offset_x;
	int		offset_y;
	int		view_dist;
	int		tile_size;
}	t_minimap;



typedef struct s_ray     //还没有init  因为不是data的成员
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_dist;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;


typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	t_wholemap	wholemap;
	char		**map;
	t_player	player;
	t_ray		ray;
	int			**texture_pixels;
	int			**textures;
	t_texinfo	texinfo;
	t_img		playermap;
}	t_data;

// Check valid
int		file_valid(char *file);
int		path_valid(char *path);
int 	check_digit(char *line);
int		check_color(char *line);
int		check_texture(char *line);
int		check_cub_file(char *path);
int 	check_map(t_data *data);
char	**split_color(char *line);


// Utils
void	jump_space(char *line);
int		error_exit(char *s);
int		error_msg(char *str, int error);
void	free_tab(char **tab);

// Parsing
int 	count_map_lines(t_data *data, char **map, int i);
int		fill_map_tab(t_wholemap *wholemap, char **map_tab, int start);
int 	parse_map(t_data *data, char **map);
int		parse_texture(t_texinfo *texinfo, char *line);
int		parse_color(t_texinfo *texinfo, int *color, char *line);
int		parse_line(t_data *data, char *line);
int		parse_cub_file(t_data *data, char *path);

// Init

void	init_data(t_data *data);
#endif