/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:20:39 by joe               #+#    #+#             */
/*   Updated: 2024/03/07 15:15:27 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Free the memory of a matrix
 * @param mat 
 */
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
/**
 * @brief Free a pointer
 * @param str 
 */
void	free_ptr(char **str)
{
	free (*str);
	*str = NULL;
}
/**
 * @brief Free the memory of the struct cub
 * @param cub 
 */
void	free_memory(t_cub *cub)
{
// 	if (cub -> textures.north_image)
// 		mlx_destroy_image (cub -> mlx, cub -> textures.north_image);
// 	if (cub -> textures.south_image)
// 		mlx_destroy_image (cub -> mlx, cub -> textures.south_image);
// 	if (cub -> textures.west_image)
// 		mlx_destroy_image (cub -> mlx, cub -> textures.west_image);
// 	if (cub -> textures.east_image)
// 		mlx_destroy_image (cub -> mlx, cub -> textures.east_image);
// 	if (cub -> img.img_info)
// 		mlx_destroy_image (cub -> mlx, cub -> img.img_info);
// 	if (cub -> mlx && cub -> win)
// 		mlx_destroy_window (cub -> mlx, cub -> win);
// 	if (cub -> mlx)
// 		mlx_destroy_display (cub -> mlx);
//	free_mat (&cub -> scene_map);
// 	free_ptr ((char **)&cub -> mlx);
// 	free_ptr (&cub -> textures.north_file);
// 	free_ptr (&cub -> textures.south_file);
// 	free_ptr (&cub -> textures.west_file);
// 	free_ptr (&cub -> textures.east_file);
	printf("O arquivo %s é invalido \n", cub -> path_maps);
}