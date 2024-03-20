/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: everton <everton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:10:34 by everton           #+#    #+#             */
/*   Updated: 2024/03/19 19:07:10 by everton          ###   ########.fr       */
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
# include <mlx.h>
# include <libft.h>

/* -------------------------------------------------------------------------- */
/* DEFINES                                                                    */
/* -------------------------------------------------------------------------- */
# define WIN_NAME "Cub3d"
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define PI 3.14159265358979323846
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
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124

/* -------------------------------------------------------------------------- */
/* STRUCTURES                                                                 */
/* -------------------------------------------------------------------------- */

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
	double	x;
	double	y;
	double	dir;
	double	dir_x;
	double	dir_y;
}	t_player;

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
	t_player	player;
	t_map		*map;
}	t_cub;

/* -------------------------------------------------------------------------- */
/* PROTOTYPES                                                                 */
/* -------------------------------------------------------------------------- */

void	cub_init(t_cub *cub, char *file);
void	cub_check_args(int argc, char **argv);


#endif
