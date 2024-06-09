/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 11:27:05 by joe               #+#    #+#             */
/*   Updated: 2024/06/09 18:11:12 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief 
 * A função set_temp() aloca memória para um novo array de strings 
 * que terá o mesmo tamanho que o mapa original. Essencialmente, esta função 
 * aloca memória para um novo array de strings e preenche cada string 
 * com espaços em branco, criando um mapa vazio do mesmo 
 * tamanho que o mapa original.
 * 
 * @param temp Um ponteiro para o ponteiro do novo array de strings.
 * @param map_height A altura do mapa original.
 * @param map_width A largura do mapa original.
 * 
 * @return Esta função não retorna um valor.
 * 
 */
static void	set_temp(char ***map, size_t map_height, size_t map_width)
{
	size_t	i;
	size_t	j;
	size_t	temp;

	map[0] = ft_calloc (map_height + 1, sizeof (char *));
	temp = map_height;
	while (temp--)
		map[0][temp] = ft_calloc (map_width + 1, sizeof (char *));
	i = 0;
	while (map_height--)
	{
		j = 0;
		temp = map_width;
		while (temp--)
		{
			map[0][i][j] = ' ';
			j++;
		}
		i++;
	}
}

/**
 * @brief 
 * Esta função determina a posição inicial e a direção 
 * do jogador dentro do mapa.
 * 
 * @param cub Um ponteiro para a estrutura `t_cub`, 
 * que contém informações sobre o mapa e o jogador.
 * @param x A coordenada x da posição inicial do jogador no mapa.
 * @param y A coordenada y da posição inicial do jogador no mapa.
 * 
 * @return Esta função não retorna um valor.
 */
static void	get_direction(t_cub *cub, size_t x, size_t y)
{
	// Define as coordenadas do jogador como o centro da célula
	cub -> p.x = x + 0.5;
	cub -> p.y = y + 0.5;
	//Coordenadas da coluna onde o jogador está na tela
	cub -> p.col_x = x * (WIN_WIDTH / cub -> map_width);
	cub -> p.col_y = y * (WIN_HEIGHT / cub -> map_height);
	cub -> p.direction = cub -> scene_map[y][x];
	if (cub -> scene_map[y][x] == 'N')
		cub -> p.ang = PI / 2;
	if (cub -> scene_map[y][x] == 'E')
		cub -> p.ang = PI;
	if (cub -> scene_map[y][x] == 'S')
		cub -> p.ang = 3 * PI / 2;
	cub -> p.dx = cos (cub -> p.ang);
	cub -> p.dy = sin (cub -> p.ang);
}

/**
 * @brief 
 * Esta função identifica a posição inicial e a direção do jogador 
 * no mapa e atualiza as informações do jogador.
 * 
 * @param cub Um ponteiro para a estrutura `t_cub`, 
 * que contém informações sobre o mapa e o jogador.
 * 
 * @return Esta função não retorna um valor.
 */
void	get_player_info(t_cub *cub)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (cub -> scene_map && cub -> scene_map[y])
	{
		x = 0;
		while (cub -> scene_map[y] && cub -> scene_map[y][x])
		{
			if (ft_strchr ("NSWE", cub -> scene_map[y][x]))
				get_direction (cub, x, y);
			x++;
		}
		y++;
	}
}

/**
 * @brief 
 * A função format_map() reformata o mapa, substituindo caracteres 
 * de nova linha por espaços e atualizando o ponteiro do mapa.
 * 
 * @param map Um ponteiro para o ponteiro do array de strings que representa o mapa.
 * @param map_height A altura atual do mapa.
 * @param map_width A largura atual do mapa.
 * 
 * @return Esta função não retorna um valor.
 */
void	format_map(char ***map, size_t map_height, size_t map_width)
{
	char	**temp;
	size_t	i;
	size_t	j;

	set_temp(&temp, map_height, map_width);
	i = 0;
	while (map[0] && map[0][i])
	{
		j = 0;
		while (map[0][i] && map[0][i][j])
		{
			if (map[0][i][j] == '\n')
				map[0][i][j] = ' ';
			temp[i][j] = map[0][i][j];
			j++;
		}
		i++;
	}
	free_mat (map);
	map[0] = temp;
}