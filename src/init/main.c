/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:02:31 by everton           #+#    #+#             */
/*   Updated: 2024/04/06 12:42:50 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



int	is_surrounded_walls(t_cub *cub)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < cub->map->height)
	{
		j = 0;
		while (cub->map->map_lines[i][j])
		{
			if (cub->map->map_lines[i][j] == ' ')
			{
				if ((i == 0 && j == 0) || (i == 0 && j == cub->map->width - 1) ||
					(i == cub->map->height - 1 && j == 0) || (i == cub->map->height - 1 && j == cub->map->width - 1))
				{
					printf("Error: map is not surrounded by walls\n");
					return (1);
				}
				else if (i == 0 || i == cub->map->height - 1 || j == 0 || j == cub->map->width - 1 ||
						 cub->map->map_lines[i - 1][j] == ' ' || cub->map->map_lines[i + 1][j] == ' ' ||
						 cub->map->map_lines[i][j - 1] == ' ' || cub->map->map_lines[i][j + 1] == ' ')
				{
					printf("Error: map is not surrounded by walls\n");
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}



void	get_direction(t_cub *cub, size_t x, size_t y)
{
	cub->player.x = x + 0.5;
	cub->player.y = y + 0.5;
	if (cub->map->map_lines[y][x] == 'N')
	{
		cub->player.dir = PI / 2;
		cub->player.dir_x = -1;
		cub->player.dir_y = 0;
	}
	else if (cub->map->map_lines[y][x] == 'S')
	{
		cub->player.dir = 3 * PI / 2;
		cub->player.dir_x = 1;
		cub->player.dir_y = 0;
	}
	else if (cub->map->map_lines[y][x] == 'W')
	{
		cub->player.dir = PI;
		cub->player.dir_x = 0;
		cub->player.dir_y = -1;
	}
	else if (cub->map->map_lines[y][x] == 'E')
	{
		cub->player.dir = 0;
		cub->player.dir_x = 0;
		cub->player.dir_y = 1;
	}
}

// A função get_player_info percorre o mapa do jogo e identificar a posição inicial e a direção do jogador, representado por um dos caracteres 'N', 'S', 'W' ou 'E', indicando a direção para a qual o jogador está olhando.




// Função que inicia o jogo
void	cub_start(t_cub *cub)
{
	printf("\n\nIN CUB_START\n");

	cub->mlx = mlx_init();
	if (!cub->mlx)
	{
		printf("Error: mlx_init failed\n");
		exit(EXIT_FAILURE);
	}
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!cub->win)
	{
		printf("Error: mlx_new_window failed\n");
		exit(EXIT_FAILURE);
	}
	render_frame(cub);
	mlx_loop(cub->mlx);

	printf("\n\nOUT CUB_START\n");
}


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
		print_read_map_lines(&cub);
	printf("\n-----------------------------------\n");

	cub_start(&cub);
	return (0);
}
