/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:10:34 by everton           #+#    #+#             */
/*   Updated: 2024/06/02 16:55:13 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CUB3D_H
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
# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define FOV 60
# define TILE_SIZE 64
# define MOVE_SPEED 0.1
# define ROTATE_SPEED 0.05
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3
# define WALL 1
# define SPRITE 2
# define EMPTY 0
# define PLAYER 3



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

# define MAX_DIST 1000000000
# define MAX_RAYS 480
# define RAY_HORIZONTAL_SIZE 16
# define FOV 60
# define WALL_HEIGHT 700

# define PRECISION_DOWN 0.00001
# define PRECISION_UP 1

# define STEPS 0.25
# define TURN_ANG 0.07


// # define KEY_ESC 53
// # define KEY_W 13
// # define KEY_A 0
// # define KEY_S 1
// # define KEY_D 2
// # define KEY_LEFT 123
// # define KEY_RIGHT 124

/* -------------------------------------------------------------------------- */
/* MACROS                                                                */
/* -------------------------------------------------------------------------- */

# define ERROR_NUMB_ARG "Error\nInvalid number of arguments.\n"
# define ERROR_EXTENSION "Error\nInvalid file extension.\n"
# define ERROR_MEMORY "Error:\nMemory allocation failed\n"
# define ERROR_INVALID_MAP "Error:\nInvalod map\n"
# define ERROR_RGB "Error:\n RGB values out of range (0-255)\n"
# define ERROR_MSG "\033[1;31mError\n\033[0m"
# define EXIT_MSG "\033[1;31mTO EXIT CUB3D!\n\033[0m"
/* -------------------------------------------------------------------------- */
/* STRUCTURES                                                                 */
/* -------------------------------------------------------------------------- */

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
	int	r;
	int	g;
	int	b;
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
	t_color	floor_color;
	t_color	ceiling_color;
	t_color	color;
}	t_img;

typedef struct s_texture
{
	t_img	north;
	t_img	south;
	t_img	east;
	t_img	west;
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

typedef struct s_map
{
	char	**map_file;
	char	**map_lines;
	int		start_map;
	size_t	width;
	size_t	height;
}	t_map;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_texture	texture;
	t_player	p;
	t_map		*map;
	t_keys		keys;
}	t_cub;




/* -------------------------------------------------------------------------- */
/* draw_background.c                                                             */
/* -------------------------------------------------------------------------- */

int	is_surrounded_walls(t_cub *cub);
void	get_direction(t_cub *cub, size_t x, size_t y);
void	cub_start(t_cub *cub);



/* ------------------------------------------------------------------------- */
/* check_map                                                          		 */
/* ------------------------------------------------------------------------- */

void	read_map_file(t_cub *cub, char *filename);
void	cub_check_args(int argc, char **argv);



/* ------------------------------------------------------------------------- */
/* cub_init                                                          		 */
/* ------------------------------------------------------------------------- */

void	set_zero(t_cub *cub);
void	parse_map_file_lines(t_cub *cub);
void	cub_init(t_cub *cub, char *file);



/* ------------------------------------------------------------------------- */
/* mlx_init                                                          		 */
/* ------------------------------------------------------------------------- */

void	draw_pixel(t_cub *cub, int x, int y, t_color color);
void	load_texture(t_cub *cub, t_img *texture);
void	render_textures(t_cub *cub);
void 	draw_background(t_cub *cub);
void	cub_mlx_init(t_cub *cub);



/* ------------------------------------------------------------------------- */
/* parse                                                        		 */
/* ------------------------------------------------------------------------- */

void	parse_color_line(char *str, t_img *img);
int	is_texture_or_color_line(t_cub *cub, char *str);
int	is_texture_or_color(char *str);
int	is_map_line(char *str);
void	print_read_map_lines(t_cub *cub);
void	parse_texture_line(char *str, t_texture *texture);
void	parse_map_line(t_cub *cub, char *str);
int		parser_cub(t_cub *cub);



/* ------------------------------------------------------------------------- */
/* utils                                                        		 */
/* ------------------------------------------------------------------------- */

int	is_empty_or_spaces(char *str);
int	check_chars(t_cub *cub);
void	get_player_info(t_cub *cub);
void	print_read_map_file(t_cub *cub);


/* ------------------------------------------------------------------------- */
/* cub_free                                                        		 */
/* ------------------------------------------------------------------------- */

void	free_mat(char ***mat);
void	free_ptr(char **str);
void	free_memory(t_cub *cub);


/* ------------------------------------------------------------------------- */
/* cub_exit                                                       		 */
/* ------------------------------------------------------------------------- */

int	cub_close(t_cub *cub);
void	cub_exit(t_cub *cub, const char *msg, const int code);


//void	print_read_map_file(t_cub *cub);


/* ------------------------------------------------------------------------- */
/* actions                                                       		 */
/* ------------------------------------------------------------------------- */

int	button_down(int key_code, t_cub *cub);
int	button_up(int key_code, t_cub *cub);


/* ------------------------------------------------------------------------- */
/* movements                                                      		 */
/* ------------------------------------------------------------------------- */

void	check_keys(t_cub *cub);

/* ------------------------------------------------------------------------- */
/* cub_run                                                      		 */
/* ------------------------------------------------------------------------- */

void	cub_run(t_cub *cub);

#endif
