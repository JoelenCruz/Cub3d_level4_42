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

static void	cub_bzero(t_cub *cub)
{
	cub->map = ft_calloc(1, sizeof(t_map));//tem ponteiro de ponteiro?
	if (!cub->map)
	{
		printf(ERROR_MEMORY);
		exit(EXIT_FAILURE);
	}
	ft_bzero (&cub -> mlx, sizeof (void));
	ft_bzero (&cub -> win, sizeof (void));
	ft_bzero (&cub -> img, sizeof (t_img));
	ft_bzero (&cub -> texture, sizeof (t_texture));
	//ft_bzero (&cub -> keys, sizeof (t_keys));
	ft_bzero (&cub -> p, sizeof(t_player));
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
	cub_bzero(cub);
	read_map_file(cub, file);
	if (parser_cub(cub))
	{
		printf(ERROR_INVALID_MAP);
		exit(EXIT_FAILURE);
	}
	get_player_info(cub);
	printf("player.x: %f\n", cub->p.x);
	printf("player.y: %f\n", cub->p.y);
	printf("player.dir: %f\n", cub->p.ang);
	printf("player.dir_x: %f\n", cub->p.dx);
	printf("player.dir_y: %f\n", cub->p.y);

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