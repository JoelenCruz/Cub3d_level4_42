
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


void	cub_start(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
	{
		printf("Error: mlx_init failed\n");
		exit(EXIT_FAILURE);
	}
	cub->win = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);

	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	if (!cub->win)
	{
		printf("Error: mlx_new_window failed\n");
		exit(EXIT_FAILURE);
	}
	draw_background(cub);
	mlx_loop(cub->mlx);
}

// static int	render(t_cub *cub)
// {
// 	check_keys (cub);
// 	cub_start(cub);
// 	//raycast (cub);
// 	mlx_put_image_to_window (cub -> mlx, cub -> win, cub->img.info, 0, 0);
// 	return (0);
// }

// /*
// *Em resumo, enquanto mlx_new_image é usada para criar uma imagem, mlx_put_image_to_window 
// *é usada para exibir essa imagem em uma janela. Ambas são partes essenciais do processo de renderização 
// de imagens em programas gráficos utilizando a biblioteca Minilibx.
// */
// void	cub_run(t_cub *cub)
// {
// 	printf("estou aqui!!! cub_run");
// 	//render(cub);
// 	mlx_loop_hook (cub -> mlx, render, cub);
// 	mlx_loop(cub -> mlx);
// }