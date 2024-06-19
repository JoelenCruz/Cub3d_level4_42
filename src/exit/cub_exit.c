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

static void	close_fds(int lower, int higger)
{
	while (lower <= higger)
		close (lower++);
}

static void	print_exit_message(const char *msg, const int code)
{
	if (code)
		ft_putstr_fd (ERROR_MSG, 1);
	if (msg)
		ft_putendl_fd ((char *) msg, 1);
	if (!code && !msg)
		ft_putendl_fd (EXIT_MSG, 1);
}

int	cub_close(t_cub *cub)
{
	cub_exit (cub, NULL, 0);
	return (0);
}

void	cub_exit(t_cub *cub, const char *msg, const int code)
{
	print_exit_message(msg, code);
	free_memory (cub);
	close_fds (0, 1023);
	exit (code);
}
