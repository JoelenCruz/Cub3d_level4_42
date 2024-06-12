

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


void draw_background(t_cub *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			draw_pixel (&cub -> img, x, y, cub -> colors.ceiling);
			draw_pixel (
				&cub -> img, x, y + WIN_HEIGHT / 2, \
				cub -> colors.floor \
			);
			x++;
		}
		y++;
	}
}

