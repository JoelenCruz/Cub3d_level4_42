
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

// void	cub_start(t_cub *cub)
// {
// 	//cub->img.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	
// 	if (!cub->win)
// 	{
// 		printf("Error: mlx_new_window failed\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	//draw_background(cub);
	
	
// 	//mlx_loop(cub->mlx);
// }

static int	render(t_cub *cub)
{
	check_keys (cub);
	draw_background(cub);
	raycast (cub);
	mlx_put_image_to_window (cub -> mlx, cub -> win, cub -> img.info, 0, 0);
	return (0);
}


void	cub_run(t_cub *cub)
{
	printf("cub_run");

	mlx_loop_hook (cub -> mlx, render, cub);
	mlx_loop(cub -> mlx);
}