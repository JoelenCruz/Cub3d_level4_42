/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 11:21:30 by joe               #+#    #+#             */
/*   Updated: 2024/06/09 19:52:25 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief 
 * A função cub_bzero() inicializa todos os campos da estrutura t_cub para zero ou NULL, 
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


/**
 * @brief 
 * A função cub_init() inicializa a estrutura t_cub com base nos argumentos fornecidos, 
 * carrega os dados da cena, formata o mapa, obtém as informações do jogador e 
 * inicializa o sistema gráfico.
 * 
 * @param cub Um ponteiro para a estrutura t_cub que será inicializada.
 * @param argv Uma matriz de strings contendo os argumentos da linha de comando. 
 *             O segundo argumento (argv[1]) deve ser o nome do arquivo de descrição da cena.
 * 
 * @return Esta função não retorna um valor.
 */
void	cub_init(t_cub *cub, char **argv)
{
	cub_bzero(cub);
	cub -> scene_description = argv[1];
	get_scene_description_data(cub);
	format_map (&cub -> scene_map, cub -> map_height, cub -> map_width);
	cub -> map_width--;
	get_player_info (cub);
	if (!cub->scene_map || !(int)cub -> p.y || !cub -> p.x)
		cub_exit (cub, "Invalid scene information.", 1);
	check_map(cub);
	cub_mlx_init(cub);
}