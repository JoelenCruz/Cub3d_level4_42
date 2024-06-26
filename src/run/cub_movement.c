/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_movement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evdos-sa <evdos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 11:21:30 by joe               #+#    #+#             */
/*   Updated: 2024/06/22 14:27:39 by evdos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	player_move(t_cub *cub, double new_x, double new_y)
{
	int	x_forward;
	int	y_forward;

	x_forward = (int)(cub -> p.x + (new_x * 8) * STEPS);
	y_forward = (int)(cub -> p.y + (new_y * 8) * STEPS);
	if (cub -> scene_map[(int)cub -> p.y][x_forward] != '1')
	{
		cub -> p.x += new_x * STEPS;
		cub -> p.col_x = ceil(x_forward * (WIN_WIDTH / cub -> map_width));
	}
	if (cub -> scene_map[y_forward][(int)cub -> p.x] != '1')
	{
		cub -> p.y += new_y * STEPS;
		cub -> p.col_y = ceil(y_forward * (WIN_HEIGHT / cub -> map_height));
	}
}

static void	player_turn(t_cub *cub, int direction)
{
	if (direction == LEFT)
		cub -> p.ang -= TURN_ANG + (cub -> p.ang < 0) * (2 * PI);
	else
		cub -> p.ang += TURN_ANG - (cub -> p.ang > 2) * (2 * PI);
	if (cub -> p.ang < 0)
		cub -> p.ang += 2 * PI;
	if (cub -> p.ang > 2 * PI)
		cub -> p.ang -= 2 * PI;
	cub -> p.dx = cos (cub -> p.ang);
	cub -> p.dy = sin (cub -> p.ang);
}

void	check_keys(t_cub *cub)
{
	if (cub -> keys.esc == PRESSED)
		cub_exit (cub, NULL, 0);
	if (cub -> keys.up == PRESSED || cub -> keys.w == PRESSED)
		player_move (cub, -cub -> p.dx * STEPS, -cub -> p.dy * STEPS);
	if (cub -> keys.down == PRESSED || cub -> keys.s == PRESSED)
		player_move (cub, cub -> p.dx * STEPS, cub -> p.dy * STEPS);
	if (cub -> keys.a == PRESSED)
		player_move (cub, -cub -> p.dy * STEPS, cub -> p.dx * STEPS);
	if (cub -> keys.d == PRESSED)
		player_move (cub, cub -> p.dy * STEPS, -cub -> p.dx * STEPS);
	if (cub -> keys.left == PRESSED)
		player_turn (cub, LEFT);
	if (cub -> keys.right == PRESSED)
		player_turn (cub, RIGHT);
}
