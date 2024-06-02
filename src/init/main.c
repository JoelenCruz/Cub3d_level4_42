/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:02:31 by everton           #+#    #+#             */
/*   Updated: 2024/06/02 18:19:40 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	main(int argc, char **argv)
{
	t_cub	cub;

	cub_check_args(argc, argv);
	cub_init(&cub, argv[1]);

					printf("\n-----------------------------------");
					printf("\n\nMAIN\n");

					printf("\n\nmap_file\n\n");
					if (cub.map->map_file != NULL)
						print_read_map_file(&cub);

					printf("\n\ntexture path\n\n");
					printf("NORTH: %s\n", cub.texture.north.path);
					printf("SOUTH: %s\n", cub.texture.south.path);
					printf("WEST: %s\n", cub.texture.west.path);
					printf("EAST: %s\n", cub.texture.east.path);

					printf("\n\nRGB\n\n");
					printf("img->floor_color.r: %d\n", cub.img.floor_color.r);
					printf("img->floor_color.g: %d\n", cub.img.floor_color.g);
					printf("img->floor_color.b: %d\n", cub.img.floor_color.b);
					printf("img->ceiling_color.r: %d\n", cub.img.ceiling_color.r);
					printf("img->ceiling_color.g: %d\n", cub.img.ceiling_color.g);
					printf("img->ceiling_color.b: %d\n", cub.img.ceiling_color.b);

					printf("\n\ncolor path\n\n");
					printf("FLOOR: %d %d %d\n", cub.img.floor_color.r, cub.img.floor_color.g, cub.img.floor_color.b);
					printf("CEILING: %d %d %d\n", cub.img.ceiling_color.r, cub.img.ceiling_color.g, cub.img.ceiling_color.b);

					printf("\n\nmap_lines\n\n");
					if (cub.map->map_lines != NULL)
						parse_map_file_lines(&cub);
					printf("\n-----------------------------------\n");

	//cub_run(&cub);
	cub_start(&cub);
	return (0);
}
