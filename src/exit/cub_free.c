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

void	free_mat(char ***mat)
{
	size_t	i;

	i = 0;
	while (*mat && mat[0][i])
		free_ptr (&mat[0][i++]);
	if (*mat)
		free (*mat);
	*mat = NULL;
}

void	free_ptr(char **str)
{
	free (*str);
	*str = NULL;
}


void	free_memory(t_cub *cub)
{
	// if (cub -> texture.north)
	// 	mlx_destroy_image (cub -> mlx, cub -> texture.north);
	// if (cub -> texture.south)
	// 	mlx_destroy_image (cub -> mlx, cub -> texture.south);
	// if (cub -> texture.west)
	// 	mlx_destroy_image (cub -> mlx, cub -> texture.west);
	// if (cub -> texture.east)
	// 	mlx_destroy_image (cub -> mlx, cub -> texture.east);
	// if (cub -> img.img_info)
	// 	mlx_destroy_image (cub -> mlx, cub -> img.img_info);
	
    if (cub -> mlx && cub -> win)
		mlx_destroy_window (cub -> mlx, cub -> win);
	
    if (cub -> mlx)
		mlx_destroy_display (cub -> mlx);
	
    // free_mat (&cub -> map);
	
    free_ptr ((char **)&cub -> mlx);
	

	// free_ptr (&cub -> texture.north);
    // free_ptr (&cub -> texture.south);
    // free_ptr (&cub -> texture.east);
    // free_ptr (&cub -> texture.west);
}