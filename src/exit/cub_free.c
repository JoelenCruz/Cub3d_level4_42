/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 11:22:44 by joe               #+#    #+#             */
/*   Updated: 2024/06/09 18:48:16 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_mat(char ***mat)
{
	size_t	i;

	i = 0;
	while (*mat && (*mat)[i])
	{
		free ((*mat)[i]);
		(*mat)[i] = NULL;
		i++;
	}
	free (*mat);
	*mat = NULL;
}

void	free_ptr(char **str)
{
	if (*str)
	{
		free (*str);
		*str = NULL;
	}
}

void	free_memory(t_cub *cub)
{
	if (cub -> scene_map)
		free_mat(&cub->scene_map);
	if (cub -> texture.north_file)
		free_ptr(&cub->texture.north_file);
	if (cub -> texture.south_file)
		free_ptr(&cub->texture.south_file);
	if (cub -> texture.west_file)
		free_ptr(&cub->texture.west_file);
	if (cub -> texture.east_file)
		free_ptr(&cub->texture.east_file);
	if (cub -> mlx && cub -> win)
		mlx_destroy_window (cub -> mlx, cub -> win);
	if (cub -> mlx)
		mlx_destroy_display (cub -> mlx);
	free_ptr ((char **)&cub -> mlx);
}
