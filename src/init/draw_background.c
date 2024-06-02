

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-02 12:03:41 by joe               #+#    #+#             */
/*   Updated: 2024-06-02 12:03:41 by joe              ###   ########.fr       */
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
	cub->p.x = x + 0.5;
	cub->p.y = y + 0.5;
	if (cub->map->map_lines[y][x] == 'N')
	{
		cub->p.ang = PI / 2;
		cub->p.dx = -1;
		cub->p.dy = 0;
	}
	else if (cub->map->map_lines[y][x] == 'S')
	{
		cub->p.ang = 3 * PI / 2;
		cub->p.x = 1;
		cub->p.y = 0;
	}
	else if (cub->map->map_lines[y][x] == 'W')
	{
		cub->p.ang = PI;
		cub->p.dx = 0;
		cub->p.dy = -1;
	}
	else if (cub->map->map_lines[y][x] == 'E')
	{
		cub->p.ang = 0;
		cub->p.dx = 0;
		cub->p.dy = 1;
	}
}

// A função get_player_info percorre o mapa do jogo e identificar a posição inicial e a direção do jogador, 
//representado por um dos caracteres 'N', 'S', 'W' ou 'E', indicando a direção para a qual o jogador está olhando.



void draw_background(t_cub *cub)
{
	int	y;
	int	x;

	y = 0;
	while (y < WIN_HEIGHT / 2)	// Preenche a metade superior da tela com a cor do teto
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			draw_pixel(cub, x, y, cub->img.ceiling_color);
			x++;
		}
		y++;
	}
	y = WIN_HEIGHT / 2;	// Preenche a metade inferior da tela com a cor do chão
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			draw_pixel(cub, x, y, cub->img.floor_color);
			x++;
		}
		y++;
	}
	render_textures(cub);
	mlx_hook(cub->win, 2, (1L << 0), button_down, cub);
	mlx_hook(cub->win, 3, (1L << 1), button_up, cub);
}