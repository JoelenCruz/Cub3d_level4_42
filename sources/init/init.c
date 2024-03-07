/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:57:55 by joe               #+#    #+#             */
/*   Updated: 2024/03/07 15:17:23 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Initializes the struct cub with zeros
 * @param cub 
 */
static void	cub_bzero(t_cub *cub)
{
	ft_bzero(cub, sizeof (t_cub));
}

/**
 * @brief Exits the program with a message
 * @param cub 
 * @param msg 
 * @param status 
 */
static void	check_argcs(int argc, t_cub *cub)
{
	if (argc != 2)
		cub_exit(cub, ERROR_ARGS, 1);
}

/**
 * @brief verify if the file extension is ".cub"
 * 
 * @param map_name 
 * @param cub 
 */
static void verify_path(char *map_name, t_cub *cub)
{
    cub -> path_maps = map_name;
    if (ft_strncmp(map_name + ft_strlen(map_name) - 4, ".cub", 4) != 0)
        cub_exit(cub, ERROR_EXTETION, 1);
}

/**
 * @brief Initializes the struct cub
 * @param argc 
 * @param argv 
 * @param cub 
 */
void	cub_init(int argc, char *argv[], t_cub *cub)
{
	cub_bzero(cub);
	check_argcs(argc, cub);
	verify_path(argv[1], cub);
}

