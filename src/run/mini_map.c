/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 19:28:37 by joe               #+#    #+#             */
/*   Updated: 2024/06/09 20:00:35 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void draw_rectangle_2(void *mlx, void *win, int x, int y, int width, int height, int color)
{
    int i, j;
    for (i = x; i < x + width; i++)
    {
        for (j = y; j < y + height; j++)
        {
            mlx_pixel_put(mlx, win, i, j, color);
        }
    }
}


void render_mini_map(t_cub *cub)
{
    // Defina o tamanho e a posição da janela do mini-mapa
    int mini_map_width = 200;
    int mini_map_height = 200;
    int mini_map_x = WIN_WIDTH - mini_map_width - 10;
    int mini_map_y = 10;

    // Desenhe a moldura da janela do mini-mapa
    draw_rectangle_2(cub->mlx, cub->win, mini_map_x, mini_map_y, mini_map_x + mini_map_width, mini_map_y + mini_map_height, 0xFFFFFF);

    // Determine a escala do mini-mapa
    float scale_x = mini_map_width / (float)cub->map_width;
    float scale_y = mini_map_height / (float)cub->map_height;

    // Renderize o mapa de localização dentro da janela do mini-mapa
    for (int y = 0; y < cub->map_height; y++)
    {
        for (int x = 0; x < cub->map_width; x++)
        {
            int cell_x = mini_map_x + x * scale_x;
            int cell_y = mini_map_y + y * scale_y;
            int color = (cub->scene_map[y][x] == '1') ? 0xFFFFFF : 0x000000; // Define a cor com base no conteúdo do mapa
            draw_rectangle_2(cub->mlx, cub->win, cell_x, cell_y, cell_x + scale_x, cell_y + scale_y, color);
        }
    }

    // Desenhe o jogador como um ponto no mini-mapa
    int player_mini_map_x = mini_map_x + cub->p.x * scale_x;
    int player_mini_map_y = mini_map_y + cub->p.y * scale_y;
    mlx_pixel_put(cub->mlx, cub->win, player_mini_map_x, player_mini_map_y, 0xFF0000);
}

