/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 11:22:44 by joe               #+#    #+#             */
/*   Updated: 2024/06/09 14:41:33 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



static void	init_cub(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		cub_exit(cub, "Can't init mlx's Xserver connection.", 1);
	cub->img.info = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->img.addr = mlx_get_data_addr(cub->img.info, &cub->img.bpp, \
		&cub->img.line_len, &cub->img.endian);
}

void	init_texture(t_cub *cub)
{
	int	temp_height;
	int	temp_width;

	cub->texture.north_image = mlx_xpm_file_to_image(cub->mlx,cub->texture.north_file, &cub->texture.height, &cub->texture.width);

	temp_height = cub->texture.height;
	temp_width = cub->texture.width;

	if (cub->texture.height != cub->texture.width)
		cub_exit(cub, "All textures must be square.", 1);
	cub->texture.south_image = mlx_xpm_file_to_image(cub->mlx,cub->texture.south_file, &cub->texture.height, &cub->texture.width);
	if (temp_height != cub->texture.height || temp_width != cub->texture.width)
		cub_exit(cub, "Can't import texture south_image. ", 1);
	cub->texture.west_image = mlx_xpm_file_to_image(cub->mlx,cub->texture.west_file, &cub->texture.height, &cub->texture.width);
	if (temp_height != cub->texture.height || temp_width != cub->texture.width)
		cub_exit(cub, "Can't import texture west_image.", 1);
	cub->texture.east_image = mlx_xpm_file_to_image(cub->mlx, cub->texture.east_file, &cub->texture.height, &cub->texture.width);
	if (temp_height != cub->texture.height || temp_width != cub->texture.width)
		cub_exit(cub, "Can't import texture east_image.", 1);
}





void	cub_mlx_init(t_cub *cub)
{
	init_cub(cub);//inicar mlx
	init_texture(cub); //inicar texturas
	if (!cub->texture.north_image || !cub->texture.south_image || \
		!cub->texture.west_image || !cub->texture.east_image)
		cub_exit(cub, "Can't import texture main", 1);
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	if (!cub->win)
		cub_exit(cub, "Can't init game window.", 1);
	mlx_hook(cub->win, 2, (1L << 0), button_down, cub);
	mlx_hook(cub->win, 3, (1L << 1), button_up, cub);
	mlx_hook(cub->win, 17, 0, cub_close, cub);
}


void	draw_pixel(t_img *img, int x, int y, int color)
{
	unsigned char	*pixel;
	int				i;

	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return ;
	i = img -> bpp - 8;
	pixel = (unsigned char *)(img -> addr + (y * img -> line_len \
	+ x * (img -> bpp / 8)));
	while (i >= 0)
	{
		if (img -> endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img -> bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}


// {
// 	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
// 	{
// 		mlx_pixel_put(cub->mlx, cub->win, x, y, (color.r << 16) | (color.g << 8) | color.b);
// 	}
// }

// void	load_texture(t_cub *cub, t_img *texture)
// {
	
// 	texture->img = mlx_xpm_file_to_image(cub->mlx, texture->path, &texture->width, &texture->height);
// 	if (!texture->img)
// 	{
// 		printf("Error: failed to load texture %s\n", texture->path);
// 		exit(EXIT_FAILURE);
// 	}
// 	//texture->data = (int *)mlx_get_data_addr(texture->img, &texture->bpp, &texture->line_len, &texture->endian);
// 	printf("\n\nOUT LOAD_TEXTURE\n");
// }

// void	draw_texture(t_cub *cub, t_img *texture, int x, int y)
// {
// 	int tex_x;
// 	int tex_y;
// 	int color;

// 	printf("\n\nIN DRAW_TEXTURE\n");

// 	tex_x = (int)(cub->map->width * cub->p.x);
// 	tex_y = (int)(cub->map->height * cub->p.y);

// 	// Verifica se as coordenadas estão dentro dos limites da janela
// 	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
// 	{
// 		color = texture->data[tex_y * texture->width + tex_x];
// 		mlx_pixel_put(cub->mlx, cub->win, x, y, color);
// 	}

// 	printf("\n\nOUT DRAW_TEXTURE\n");
// }

// Função para desenhar as texturas na tela

