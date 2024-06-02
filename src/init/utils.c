/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 11:27:05 by joe               #+#    #+#             */
/*   Updated: 2024/06/02 15:02:45 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief 
 * A função is_empty_or_spaces() verifica se uma string é composta apenas por espaços em branco. 
 * Se a string contiver apenas espaços em branco, a função retorna 1. Caso contrário, retorna 0.
 * 
 * @param str A string a ser verificada.
 * 
 * @return Retorna 1 se a string for composta apenas por espaços em branco, caso contrário, 
 * retorna 0.
 */
int	is_empty_or_spaces(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief 
 * A função check_chars() verifica se o mapa contém apenas caracteres válidos, que podem ser ' ', '0', '1' 
 * ou caracteres representando a posição inicial do jogador ('N', 'S', 'E' ou 'W'). 
 * Se encontrar um caractere inválido, imprime uma mensagem de erro indicando o caractere inválido 
 * encontrado e retorna 1. Caso contrário, retorna 0, indicando que todos os caracteres são válidos.
 * 
 * @param cub Um ponteiro para a estrutura t_cub que contém o mapa a ser verificado.
 * 
 * @return Retorna 1 se encontrar um caractere inválido no mapa, caso contrário, retorna 0.
 */
int	check_chars(t_cub *cub)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < cub->map->height)
	{
		j = 0;
		while (cub->map->map_lines[i][j])
		{
			if (cub->map->map_lines[i][j] == '\n' && cub->map->map_lines[i][j + 1] == '\0')
				break;
			if (ft_strchr(" 01NSEW", cub->map->map_lines[i][j]) == NULL)
			{
				printf("cub->map->map_lines[%li][%li]: %c\n", i, j, cub->map->map_lines[i][j]);
				printf("cub->map->map_lines[%li][%li]: %i\n", i, j, cub->map->map_lines[i][j]);
				printf("Error: invalid character in map\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

/**
 * @brief 
 * A função get_player_info() percorre o mapa para encontrar a posição inicial do jogador ('N', 'S', 'W' ou 'E'). 
 * Quando encontra a posição inicial do jogador, chama a função get_direction() para obter a direção inicial do jogador.
 * 
 * @param cub Um ponteiro para a estrutura t_cub que contém o mapa do jogo.
 * 
 * @return Esta função não retorna um valor.
 */
void	get_player_info(t_cub *cub)
{
	size_t	i;
	size_t	x;
	size_t	y;

	printf("\n\nIN GET_PLAYER_INFO\n");

	i = 0;
	y = 0;
	while (i < cub->map->height)
	{
		x = 0;
		while (i < cub->map->height && cub->map->map_lines[y][x])
		{
			// printf("cub->map->map_lines[%li][%li]: %c\n", y, x, cub->map->map_lines[y][x]);
			if (ft_strchr ("NSWE", cub->map->map_lines[y][x]))
			{
				printf("cub->map->map_lines[%li][%li]: %c\n", y, x, cub->map->map_lines[y][x]);
				get_direction (cub, x, y);
			}
			x++;
		}
		y++;
		i++;
	}

	printf("\n\nOUT GET_PLAYER_INFO\n");
}


void	print_read_map_file(t_cub *cub)
{
	printf("\n\nIN PRINT_READ_MAP_FILE\n");
	size_t	i;

	i = 0;
	while (cub->map->map_file[i])
	{
		printf("cub->map->map_file[%li]: %s\n", i, cub->map->map_file[i]);
		i++;
	}
	printf("\n\nOUT PRINT_READ_MAP_FILE\n");
}