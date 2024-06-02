/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 11:21:30 by joe               #+#    #+#             */
/*   Updated: 2024/06/02 17:37:21 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief 
 * A função cub_bzero() inicializa todos os campos da estrutura t_cub para zero ou NULL, 
 * exceto o campo 'map', que é inicializado com uma alocação de memória de tamanho 'sizeof(t_map)' 
 * usando ft_calloc. Se a alocação de memória falhar para 'map', a função imprime uma mensagem de erro 
 * e encerra o programa.
 * 
 * @param cub Um ponteiro para a estrutura t_cub que será inicializada.
 * 
 * @return Esta função não retorna um valor.
 */
static void	cub_bzero(t_cub *cub)
{
	cub->map = ft_calloc(1, sizeof(t_map));
	if (!cub->map)
	{
		printf(ERROR_MEMORY);
		exit(EXIT_FAILURE);
	}
	ft_bzero (&cub -> mlx, sizeof (void));
	ft_bzero (&cub -> win, sizeof (void));
	ft_bzero (&cub -> img, sizeof (t_img));
	ft_bzero (&cub -> texture, sizeof (t_texture));
	ft_bzero (&cub -> p, sizeof(t_player));
}


/**
 * @brief 
 * A função cub_init() inicializa a estrutura t_cub, lendo o arquivo de configuração do jogo 
 * especificado por 'file', realizando o parsing do arquivo, obtendo informações do jogador
 * 
 * @param cub Um ponteiro para a estrutura t_cub que será inicializada.
 * @param file O nome do arquivo de configuração do jogo.
 * 
 * @return Esta função não retorna um valor.
 */

void	cub_init(t_cub *cub, char *file)
{
			printf("\n\nIN CUB_INIT\n");
	
	cub_bzero(cub);
	read_map_file(cub, file);
	if (parser_cub(cub))
	{
		printf(ERROR_INVALID_MAP);
		exit(EXIT_FAILURE);
	}
	
	get_player_info(cub);
			printf("player.x: %f\n", cub->p.x);
			printf("player.y: %f\n", cub->p.y);
			printf("player.dir: %f\n", cub->p.ang);
			printf("player.dir_x: %f\n", cub->p.dx);
			printf("player.dir_y: %f\n", cub->p.y);

	// if (!cub->map->map_lines || !cub->player.x || !cub->player.y || !cub->player.dir || !cub->player.dir_x || !cub->player.dir_y)
	// {
	// 	printf("Error\nInvalid map\n");
	// 	exit(1);
	// }

			printf("cub->texture.north.path: %s\n", cub->texture.north.path);
			printf("cub->texture.north.height: %d\n", cub->texture.north.height);
			printf("cub->texture.north.width: %d\n", cub->texture.north.width);

			printf("\n\nOUT CUB_INIT\n");
}