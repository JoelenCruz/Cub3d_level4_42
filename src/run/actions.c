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

int	button_down(int key_code, t_cub *cub)
{
	if (key_code == ESC_KEY)
		cub -> keys.esc = PRESSED;
	else if (key_code == 'w')
		cub -> keys.w = PRESSED;
	else if (key_code == 'a')
		cub -> keys.a = PRESSED;
	else if (key_code == 's')
		cub -> keys.s = PRESSED;
	else if (key_code == 'd')
		cub -> keys.d = PRESSED;
	else if (key_code == LEFT_KEY)
		cub -> keys.left = PRESSED;
	else if (key_code == UP_KEY)
		cub -> keys.up = PRESSED;
	else if (key_code == RIGHT_KEY)
		cub -> keys.right = PRESSED;
	else if (key_code == DOWN_KEY)
		cub -> keys.down = PRESSED;
	return (0);
}

int	button_up(int key_code, t_cub *cub)
{
	if (key_code == 'w')
		cub -> keys.w = RELEASED;
	else if (key_code == 'a')
		cub -> keys.a = RELEASED;
	else if (key_code == 's')
		cub -> keys.s = RELEASED;
	else if (key_code == 'd')
		cub -> keys.d = RELEASED;
	else if (key_code == LEFT_KEY)
		cub -> keys.left = RELEASED;
	else if (key_code == UP_KEY)
		cub -> keys.up = RELEASED;
	else if (key_code == RIGHT_KEY)
		cub -> keys.right = RELEASED;
	else if (key_code == DOWN_KEY)
		cub -> keys.down = RELEASED;
	return (0);
}
