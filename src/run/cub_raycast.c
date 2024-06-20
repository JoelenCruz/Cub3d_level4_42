/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:48:23 by joe               #+#    #+#             */
/*   Updated: 2024/06/09 16:48:49 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_raycast(t_cub *cub, t_raycast *rc)
{
	rc->color = 0x0000AA;
	if (cub -> map_height > cub -> map_width)
		rc->deep_of_field_max = cub -> map_height;
	else
		rc->deep_of_field_max = cub -> map_width;
	rc->ray_angle = cub -> p.ang - DR / (MAX_RAYS / FOV) * MAX_RAYS / 2;
	rc->ray = 0;
	rc -> line_y = 0;
}

void	raycast(t_cub *cub)
{
	t_raycast	rc;

	init_raycast(cub, &rc);
	while (rc.ray < MAX_RAYS)
	{
		choose_wall(cub, &rc);
		choose_texture(cub, &rc);
		draw_3d_walls(cub, &rc);
		rc.ray_angle += DR / (MAX_RAYS / FOV);
		rc.ray++;
	}
}
