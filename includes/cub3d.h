/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: everton <everton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:10:34 by everton           #+#    #+#             */
/*   Updated: 2024/06/21 12:21:33 by everton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* -------------------------------------------------------------------------- */
/* INCLUDES                                                                   */
/* -------------------------------------------------------------------------- */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

/* -------------------------------------------------------------------------- */
/* DEFINES                                                                    */
/* -------------------------------------------------------------------------- */
# define WIN_NAME "Cub3d"
# define WIN_WIDTH 960
# define WIN_HEIGHT 600
# define ESC_KEY 65307
# define LEFT_KEY 65361
# define UP_KEY 65362
# define RIGHT_KEY 65363
# define DOWN_KEY 65364
# define LEFT 1
# define RIGHT 2
# define PRESSED 1
# define RELEASED 2
# define PI 3.1415
# define DR 0.0174533
# define FOV 60
# define MAX_DIST 1000000000
# define MAX_RAYS 480
# define RAY_HORIZONTAL_SIZE 16
# define FOV 60
# define WALL_HEIGHT 700
# define PRECISION_DOWN 0.00001
# define PRECISION_UP 1
# define STEPS 0.25
# define TURN_ANG 0.07
# define MMAP_SCL 6

/* -------------------------------------------------------------------------- */
/* MACROS                                                                */
/* -------------------------------------------------------------------------- */
# define ERROR_NUMB_ARG "Error\nInvalid number of arguments."
# define ERROR_TRY_ARG " Try ./cub3d <map.cub>.\n"
# define ERROR_EXTENSION "Error\nInvalid file extension.\n"
# define ERROR_MEMORY "Error:\nMemory allocation failed\n"
# define ERROR_INVALID_MAP "Error:\nInvalod map\n"
# define ERROR_RGB "Error:\n RGB values out of range (0-255)\n"
# define ERROR_MSG "\033[1;31mError\n\033[0m"
# define EXIT_MSG "\033[1;31mTO EXIT CUB3D!\n\033[0m"
# define ERROR_SAVE_FILE "Error\nFailed to save file\n"
# define ERROR_SAVE_ARG "Error\nInvalid argument for save\n"

/* -------------------------------------------------------------------------- */
/* STRUCTURES                                                                 */
/* -------------------------------------------------------------------------- */

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_get_color
{
	size_t	start;
	char	*temp[3];
	size_t	len;
	int		ret;
}			t_get_color;

typedef struct s_keys
{
	int	esc;
	int	up;
	int	down;
	int	left;
	int	right;
	int	w;
	int	a;
	int	s;
	int	d;
}	t_keys;

typedef struct s_color
{
	int	floor;
	int	ceiling;
}	t_color;

typedef struct s_img
{
	void	*img;
	void	*info;
	void	*addr;
	char	*path;
	int		*data;
	int		bpp;
	int		line_len;
	int		endian;
	int		height;
	int		width;
}	t_img;

typedef struct s_texture
{
	int		height;
	int		width;
	char	*north_file;
	char	*south_file;
	char	*west_file;
	char	*east_file;
	void	*north_image;
	void	*south_image;
	void	*west_image;
	void	*east_image;
}	t_texture;

typedef struct s_player
{
	float	x;
	float	y;
	float	col_x;
	float	col_y;
	float	dx;
	float	dy;
	float	ang;
	int		direction;
}			t_player;

typedef struct s_raycast
{
	int		deep_of_field;
	int		deep_of_field_max;
	void	*texture;
	int		texture_x;
	int		texture_y;
	int		color;
	int		ray;
	float	ray_x;
	float	ray_y;
	float	ray_angle;
	float	ray_x_offset;
	float	ray_y_offset;
	int		ray_horizontal_size;
	float	distance;
	float	distance_horizontal;
	float	horizontal_x;
	float	horizontal_y;
	float	horizontal_tan;
	float	distance_vertical;
	float	vertical_x;
	float	vertical_y;
	float	vertical_tan;
	int		vertical_line;
	float	cast_angle;
	int		line_off;
	int		line_y;
}	t_raycast;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	char		*header;
	char		*scene_description;
	char		**scene_map;
	int			map_height;
	int			map_width;
	int			win_width;
	int			win_height;
	int			*img_save;
	int			save;
	t_img		img;
	t_texture	texture;
	t_player	p;
	t_keys		keys;
	t_color		colors;
}	t_cub;

/* ------------------------------------------------------------------------- */
/* check_map                                                          		 */
/* ------------------------------------------------------------------------- */

void	cub_check_args(int argc, char **argv);
void	check_map(t_cub *cub);

/* ------------------------------------------------------------------------- */
/* cub_init                                                          		 */
/* ------------------------------------------------------------------------- */

void	cub_init(t_cub *cub, char **argv);
int		get_color(int *color, char *line);

/* ------------------------------------------------------------------------- */
/* mlx_init                                                          		 */
/* ------------------------------------------------------------------------- */

void	draw_pixel(t_img *img, int x, int y, int color);
void	draw_background(t_cub *cub);
void	cub_mlx_init(t_cub *cub);

/* ------------------------------------------------------------------------- */
/* parse                                                         			 */
/* ------------------------------------------------------------------------- */

void	get_scene_description_data(t_cub *cub);

/* ------------------------------------------------------------------------- */
/* utils                                                   		     		 */
/* ------------------------------------------------------------------------- */

void	get_player_info(t_cub *cub);
void	format_map(char ***map, size_t map_height, size_t map_width);

/* ------------------------------------------------------------------------- */
/* cub_free                                                	        		 */
/* ------------------------------------------------------------------------- */

void	free_mat(char ***mat);
void	free_ptr(char **str);
void	free_memory(t_cub *cub);

/* ------------------------------------------------------------------------- */
/* cub_exit                                                    		   		 */
/* ------------------------------------------------------------------------- */

int		cub_close(t_cub *cub);
void	cub_exit(t_cub *cub, const char *msg, const int code);

/* ------------------------------------------------------------------------- */
/* movements                                                  	    		 */
/* ------------------------------------------------------------------------- */

void	check_keys(t_cub *cub);

/* ------------------------------------------------------------------------- */
/* cub_run                                                   		   		 */
/* ------------------------------------------------------------------------- */

void	cub_run(t_cub *cub);

/* ------------------------------------------------------------------------- */
/* actions                                                       		 */
/* ------------------------------------------------------------------------- */

int		button_down(int key_code, t_cub *cub);
int		button_up(int key_code, t_cub *cub);

/* ------------------------------------------------------------------------- */
/* raycast                                                  	    		 */
/* ------------------------------------------------------------------------- */

void	raycast(t_cub *cub);
void	reset_params(t_cub *cub, t_raycast *rc);
void	set_h_rays(t_cub *cub, t_raycast *rc);
void	set_v_rays(t_cub *cub, t_raycast *rc);
void	h_wall_hit(t_cub *cub, t_raycast *rc, int map_x, int map_y);
void	v_wall_hit(t_cub *cub, t_raycast *rc, int map_x, int map_y);
void	choose_wall(t_cub *cub, t_raycast *rc);
void	choose_texture(t_cub *cub, t_raycast *rc);
void	draw_3d_walls(t_cub *cub, t_raycast *rc);
void	draw_rectangle(t_cub *cub, t_coord start, t_coord end, int color);
float	dist(float ax, float ay, float bx, float by);
void	render_mini_map(t_cub *cub);

#endif
