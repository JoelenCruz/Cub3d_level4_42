/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 11:21:30 by joe               #+#    #+#             */
/*   Updated: 2024/04/06 13:45:48 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	set_zero(t_cub *cub)
{
	printf("\n\nIN SET_ZERO\n");

	cub->mlx = NULL;
	cub->win = NULL;
	cub->map = ft_calloc(1, sizeof(t_map));
	if (!cub->map)
	{
		printf("Error: memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	cub->map->map_file = NULL;
	cub->map->map_lines = NULL;
	cub->map->start_map = 0;
	cub->map->width = 0;
	cub->map->height = 0;
	cub->img.img = NULL;
	cub->img.path = NULL;
	cub->img.bpp = 0;
	cub->img.line_len = 0;
	cub->img.endian = 0;
	cub->img.width = 0;
	cub->img.height = 0;
	cub->img.floor_color.r = 0;
	cub->img.floor_color.g = 0;
	cub->img.floor_color.b = 0;
	cub->img.ceiling_color.r = 0;
	cub->img.ceiling_color.g = 0;
	cub->img.ceiling_color.b = 0;
	cub->texture.north.img = NULL;
	cub->texture.north.path = NULL;
	cub->texture.south.img = NULL;
	cub->texture.south.path = NULL;
	cub->texture.east.img = NULL;
	cub->texture.east.path = NULL;
	cub->texture.west.img = NULL;
	cub->texture.west.path = NULL;
	cub->player.x = 0;
	cub->player.y = 0;
	cub->player.dir = 0;
	cub->player.dir_x = 0;
	cub->player.dir_y = 0;

	printf("\n\nOUT SET_ZERO\n");
}


void	read_cub_map_file(t_cub *cub)
{
	printf("\n\nIN READ_CUB_MAP_FILE\n");

	size_t	i;

	i = 0;
	while (cub->map->map_file[i])
	{
		if (!is_empty_or_spaces(cub->map->map_file[i]))
		{
			if (!is_texture_or_color_line(cub, cub->map->map_file[i]) && is_map_line(cub->map->map_file[i]))
			{
				parse_map_line(cub, cub->map->map_file[i]);
			}
		}
		i++;
	}
	// printf("\n\n-----------------------------\n");
	// printf("\n\nREAD_CUB_MAP_FILE\n");
	// printf("img->floor_color.r: %d\n", cub->img.floor_color.r);
	// printf("img->floor_color.g: %d\n", cub->img.floor_color.g);
	// printf("img->floor_color.b: %d\n", cub->img.floor_color.b);
	// printf("img->ceiling_color.r: %d\n", cub->img.ceiling_color.r);
	// printf("img->ceiling_color.g: %d\n", cub->img.ceiling_color.g);
	// printf("img->ceiling_color.b: %d\n", cub->img.ceiling_color.b);
	// printf("\n\n-----------------------------\n");

	printf("\n\nOUT READ_CUB_MAP_FILE\n");
}


void	cub_init(t_cub *cub, char *file)
{
	printf("\n\nIN CUB_INIT\n");

	set_zero(cub);
	read_map_file(cub, file);
	if (parser_cub(cub))
	{
		printf("Error\nInvalid map\n");
		exit(1);
	}
	get_player_info(cub);
	printf("player.x: %f\n", cub->player.x);
	printf("player.y: %f\n", cub->player.y);
	printf("player.dir: %f\n", cub->player.dir);
	printf("player.dir_x: %f\n", cub->player.dir_x);
	printf("player.dir_y: %f\n", cub->player.dir_y);

	// if (!cub->map->map_lines || !cub->player.x || !cub->player.y || !cub->player.dir || !cub->player.dir_x || !cub->player.dir_y)
	// {
	// 	printf("Error\nInvalid map\n");
	// 	exit(1);
	// }

	printf("cub->texture.north.path: %s\n", cub->texture.north.path);
	printf("cub->texture.north.height: %d\n", cub->texture.north.height);
	printf("cub->texture.north.width: %d\n", cub->texture.north.width);

	printf("\n\nOUT CUB_INIT\n");
}