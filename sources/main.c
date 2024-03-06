/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:11:37 by joe               #+#    #+#             */
/*   Updated: 2024/03/06 13:08:10 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int argc, char **argv) 
{
    t_cub	cub;
    
    cub_init(argc, argv, &cub);
    printf("File extension is valid.\n");

    return 0;
}