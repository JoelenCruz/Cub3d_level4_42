/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evdos-sa <evdos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 11:21:30 by joe               #+#    #+#             */
/*   Updated: 2024/06/19 16:07:45 by evdos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	render(t_cub *cub)
{
	check_keys (cub);
	draw_background(cub);
	raycast (cub);
	render_mini_map(cub);
	mlx_put_image_to_window (cub -> mlx, cub -> win, cub -> img.info, 0, 0);
	return (0);
}

void	cub_run(t_cub *cub)
{
	mlx_loop_hook (cub -> mlx, render, cub);
	mlx_loop(cub -> mlx);
}
