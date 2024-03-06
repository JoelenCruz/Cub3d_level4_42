/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:59:33 by joe               #+#    #+#             */
/*   Updated: 2024/03/06 13:48:43 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// *=============================================================================
// *EXTERNAL LIBRARIES
// *=============================================================================

# include <errno.h>		// perror
# include <fcntl.h>		// open, close, read
# include <math.h>
# include <stddef.h>
# include <stdio.h>		// printf
# include <stdlib.h>	// malloc, free
# include <string.h>	// strerror
# include <unistd.h>	// write, exit


// *=============================================================================
// *LOCAL LIBRARIES
// *=============================================================================

# include "../minilibx_linux/mlx.h"
# include "../libft/libft.h"

// *=============================================================================
// *MACROS
// *=============================================================================

# define WIN_NAME "CUB3D jcruz-da /\ evdos-sa"
# define WIN_HEIGHT 600
# define WIN_WIDTH 960

# define ERROR_EXTETION "\033[1;31mInvalid file extension\n\033[0m\n"
# define ERROR_MSG	"\033[1;31mError: \033[0m"
# define EXIT_MSG	"\033[1;35mSee you soon, human!\033[0m"
#define  ERROR_ARGS "\033[1;31mInvalid number of arguments\n\033[0m\n"

// *=============================================================================
// *STRUCTS
// *=============================================================================

typedef struct s_cub
{
	//void		*mlx;
	//void		*win;
	char		*path_maps;
	//char		**scene_map;
	// int			map_height;
	// int			map_width;
	// t_img		img;
	// t_texture	textures;
	// t_color		colors;
	// t_keys		keys;
	// t_player	p;
}	t_cub;



// *=============================================================================
// *INIT
// *=============================================================================

void	cub_init(int argc, char *argv[], t_cub *cub);


// *=============================================================================
// *EXIT
// *=============================================================================

void	cub_exit(t_cub *cub, const char *msg, const int code);


// *=============================================================================
// *FREE
// *=============================================================================

void	free_memory(t_cub *cub);
void	free_ptr(char **str);


#endif
;