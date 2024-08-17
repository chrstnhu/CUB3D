/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrhu <chrhu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:30:47 by chrhu             #+#    #+#             */
/*   Updated: 2024/08/17 19:51:47 by chrhu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define DEF "\033[0;39m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"

#define TOP(i)    ((i) - 1)
#define DOWN(i)     ((i) + 1)
#define LEFT(j)  ((j) - 1)
#define RIGHT(j)  ((j) + 1)

#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h> //for open
#include "../minilibx-linux/mlx.h"
#include "../libft/includes/libft.h"



enum e_texture_index
{
	NO = 0,
	SO = 1,
	EA = 2,
	WE = 3,
};


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



typedef struct s_ray
{
    // 射线方向和摄像机平面的交点，用于计算射线在视锥体中的位置
    double camera_plane_x; // 更清晰地表明这是与摄像机平面的交点相关的变量
    double ray_dir_x;      // 射线在 X 方向上的方向
    double ray_dir_y;      // 射线在 Y 方向上的方向

    // 当前射线所在的地图方块坐标
    int map_grid_x;        // 射线所在的地图网格 X 坐标
    int map_grid_y;        // 射线所在的地图网格 Y 坐标

    // DDA 算法使用的步进方向
    int step_x;            // 射线沿 X 方向的步进（+1 或 -1）
    int step_y;            // 射线沿 Y 方向的步进（+1 或 -1）

    // 从起点到第一个 X 和 Y 边界的距离
    double side_dist_x;    // 射线从起点到下一个 X 边界的距离
    double side_dist_y;    // 射线从起点到下一个 Y 边界的距离

    // 每跨过一个网格的 X 和 Y 边界时射线的增量距离
    double delta_dist_x;   // 射线每前进一个网格 X 距离的增量
    double delta_dist_y;   // 射线每前进一个网格 Y 距离的增量

    // 与墙壁的碰撞相关
    double perp_wall_dist; // 射线到墙壁的垂直距离
    int hit_side;          // 射线碰到的墙壁面 (0: X方向的墙, 1: Y方向的墙)
	double wall_x;         // 射线碰到的墙壁的坐标
    // 用于渲染的变量
    int wall_line_height;  // 墙壁在屏幕上投影的高度
    int draw_start;        // 墙壁在屏幕上开始绘制的点
    int draw_end;          // 墙壁在屏幕上结束绘制的点
} t_ray;


typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	int			player_count;
	t_wholemap	wholemap;
	char		**map;
	t_player	player;
	t_ray		ray;
	int			**texture_pixels;
	int			**textures;
	t_texinfo	texinfo;
	t_img		playermap;
}	t_data;

// Check cub file
int		file_valid(char *file);
int		check_cub_file(char *path);
int		check_texture(char *line);
// Check border map
int		check_border_walls(t_data *data, char **map);
// Check rgb color
int 	check_digit(char *line);
int		check_color(char *line);
char	**split_color(char *line);
// Check map (invalid charactere, player)
int 	check_map(t_data *data);

// Utils
void	jump_space(char *line);
int		error_exit(char *s);
int		error_msg(char *str, int error);
void	free_tab(void **tab);

// Parsing
int 	count_map_lines(t_data *data, char **map, int i);
int		fill_map_tab(t_wholemap *wholemap, char **map_tab, int start);
int 	parse_map(t_data *data, char **map);
int		parse_texture(t_texinfo *texinfo, char *line);
int		parse_color(t_texinfo *texinfo, int *color, char *line);
int		parse_line(t_data *data, char *line);
int		parse_cub_file(t_data *data, char *path);


// Initialize Data
void	init_data(t_data *data);
// Initialize Texture
void	init_ray(t_ray *ray);
void	init_textures(t_data *data);
void	init_texture_pix(t_data *data);
// Initialize Minilibx
void	init_mlx(t_data *data);
void	init_img(t_data *data, t_img *image, int width, int height);
void	init_img_clean(t_img *img);
// Initialize Player
void	init_player_west_east(t_player *player);
void	init_player_north_south(t_player *player);

//main.c

//render.c

void	render_screen(t_data *data);
void	update_texture_pix(t_data *data, t_texinfo *tex, t_ray *ray, int x);
void	render_frame(t_data *data);

// Raycasting
int		raycasting(t_data *data);
void 	calc_delta_dist(t_data *data);
void 	calc_side_dist(t_data *data);
void	dda(t_data *data, t_ray *ray);
void	calculate_line_height(t_data *data, t_ray *ray);

#endif