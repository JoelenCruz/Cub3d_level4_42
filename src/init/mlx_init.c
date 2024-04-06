/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 11:22:44 by joe               #+#    #+#             */
/*   Updated: 2024/04/06 13:45:42 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"



void	draw_pixel(t_cub *cub, int x, int y, t_color color)
{
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		mlx_pixel_put(cub->mlx, cub->win, x, y, (color.r << 16) | (color.g << 8) | color.b);
	}
}

void	load_texture(t_cub *cub, t_img *texture)
{
	printf("\n\nIN LOAD_TEXTURE\n");
	texture->img = mlx_xpm_file_to_image(cub->mlx, texture->path, &texture->width, &texture->height);
	printf("texture->path: %s\n", texture->path);
	printf("texture->height: %d\n", texture->height);
	printf("texture->width: %d\n", texture->width);
	if (!texture->img)
	{
		printf("Error: failed to load texture %s\n", texture->path);
		exit(EXIT_FAILURE);
	}
	texture->data = (int *)mlx_get_data_addr(texture->img, &texture->bpp, &texture->line_len, &texture->endian);
	printf("\n\nOUT LOAD_TEXTURE\n");
}

void	draw_texture(t_cub *cub, t_img *texture, int x, int y)
{
	int tex_x;
	int tex_y;
	int color;

	printf("\n\nIN DRAW_TEXTURE\n");

	tex_x = (int)(cub->map->width * cub->player.x);
	tex_y = (int)(cub->map->height * cub->player.y);

	// Verifica se as coordenadas estão dentro dos limites da janela
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		color = texture->data[tex_y * texture->width + tex_x];
		mlx_pixel_put(cub->mlx, cub->win, x, y, color);
	}

	printf("\n\nOUT DRAW_TEXTURE\n");
}

// Função para desenhar as texturas na tela
void	render_textures(t_cub *cub)
{
	printf("\n\nIN RENDER_TEXTURES\n");

	// printf("cub->texture.north.path: %s\n", cub->texture.north.path);
	// printf("cub->texture.north.height: %d\n", cub->texture.north.height);
	// printf("cub->texture.north.width: %d\n", cub->texture.north.width);
	// Carrega as texturas
	load_texture(cub, &(cub->texture.north));
	load_texture(cub, &(cub->texture.south));
	load_texture(cub, &(cub->texture.east));
	load_texture(cub, &(cub->texture.west));

	printf("chegamos aqui !\n");

	// Desenha as texturas na tela
	draw_texture(cub, &(cub->texture.north), 0, 0);
	draw_texture(cub, &(cub->texture.south), 0, WIN_HEIGHT / 2);
	draw_texture(cub, &(cub->texture.east), WIN_WIDTH / 2, 0);
	draw_texture(cub, &(cub->texture.west), WIN_WIDTH / 2, WIN_HEIGHT / 2);

	// Libera a memória alocada para as texturas
	mlx_destroy_image(cub->mlx, cub->texture.north.img);
	mlx_destroy_image(cub->mlx, cub->texture.south.img);
	mlx_destroy_image(cub->mlx, cub->texture.east.img);
	mlx_destroy_image(cub->mlx, cub->texture.west.img);

	printf("\n\nOUT RENDER_TEXTURES\n");
}

void render_frame(t_cub *cub)
{
	int	y;
	int	x;

	y = 0;
	// Preenche a metade superior da tela com a cor do teto
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			draw_pixel(cub, x, y, cub->img.ceiling_color);
			x++;
		}
		y++;
	}

	// Preenche a metade inferior da tela com a cor do chão
	y = WIN_HEIGHT / 2;
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
}