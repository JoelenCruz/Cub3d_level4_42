/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:57:55 by joe               #+#    #+#             */
/*   Updated: 2024/03/06 13:48:11 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


static void	cub_bzero(t_cub *cub)
{
	ft_bzero(cub, sizeof (t_cub));
}

static void	check_argcs(int argc, t_cub *cub)
{
	if (argc != 2)
		cub_exit(cub, ERROR_ARGS, 1);
}


static void verify_path(char *map_name, t_cub *cub)
{
    cub -> path_maps = map_name; //salvar o nome do arquivo na struct
    
    // Verifica se o nome do arquivo termina com ".cub"
    if (ft_strncmp(map_name + ft_strlen(map_name) - 4, ".cub", 4) != 0)
        cub_exit(cub, ERROR_EXTETION, 1);
}

void	cub_init(int argc, char *argv[], t_cub *cub)
{
	cub_bzero(cub);
	check_argcs(argc, cub);
	verify_path(argv[1], cub);
}

