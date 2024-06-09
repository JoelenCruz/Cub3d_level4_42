/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 11:21:30 by joe               #+#    #+#             */
/*   Updated: 2024/06/09 14:36:55 by joe              ###   ########.fr       */
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
	ft_bzero (cub, sizeof (t_cub));
	ft_bzero (&cub -> img, sizeof (t_img));
	ft_bzero (&cub -> texture, sizeof (t_texture));
	ft_bzero (&cub -> p, sizeof(t_player));
	ft_bzero (&cub -> colors, sizeof (t_color));
}

static void	get_scene_description_file_name(char *map_name, t_cub *cub)
{
	char	*extension_start;

	cub -> scene_description = map_name;
	extension_start = ft_strrchr (cub -> scene_description, '.');
	if (ft_strncmp (extension_start, ".cub", ft_strlen (".cub") + 1))
		cub_exit (cub, "Invalid scene description file extension.", 1);
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
void	cub_init(t_cub *cub, char **argv)
{
	printf("\n\nIN CUB_INIT\n");
	
	cub_bzero(cub);
	
	get_scene_description_file_name (argv[1], cub);
	
	get_scene_description_data(cub);
	
	
	format_map (&cub -> scene_map, cub -> map_height, cub -> map_width);
	cub -> map_width--;


	get_player_info (cub);
	if (!cub->scene_map || !(int)cub -> p.y || !cub -> p.x)
		cub_exit (cub, "Invalid scene information.", 1);

	
			printf("\n\nOUT CUB_INIT\n");
	
	check_map(cub);
	cub_mlx_init(cub);
	printf("entrei aqui");
}