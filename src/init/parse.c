/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:23:54 by joe               #+#    #+#             */
/*   Updated: 2024/06/02 18:00:56 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

/**
 * @brief 
 * A função parse_color_line() analisa uma linha de entrada que contém informações
 * sobre a cor do piso ou do teto em um arquivo de configuração do jogo. Ela divide
 * a linha em partes com base nos espaços em branco e, em seguida, converte os componentes
 * RGB da cor de texto para valores inteiros e os armazena na estrutura de imagem t_img fornecida.
 *
 * @param str uma string contendo a linha de entrada que contém informações sobre a cor do piso ou do teto.
 * @param img um ponteiro para uma estrutura t_img que contém informações sobre a imagem, incluindo cores do piso e do teto.
 *
 * @return Esta função não retorna um valor.
 */
void	parse_color_line(char *str, t_img *img)
{
	char	**split;
	size_t	i;

	i = 0;
	split = ft_split(str, ' ');
	if (!split)
	{
		printf(ERROR_MEMORY);
		exit(EXIT_FAILURE);
	}
	if (split[0] && split[1] && split[2] && split[3])
	{
		if (ft_strnstr(str, "F ", ft_strlen(str)) != NULL)
		{
			if (ft_atoi(split[1]) < 0 || ft_atoi(split[1]) > 255 || ft_atoi(split[2]) < 0 || ft_atoi(split[2]) > 255 || ft_atoi(split[3]) < 0 || ft_atoi(split[3]) > 255)
			{
				printf("Error: RGB values out of range (0-255)\n");
				exit(EXIT_FAILURE);
			}
			img->floor_color.r = ft_atoi(split[1]);
			img->floor_color.g = ft_atoi(split[2]);
			img->floor_color.b = ft_atoi(split[3]);
		}
		else if (ft_strnstr(str, "C ", ft_strlen(str)) != NULL)
		{
			if (ft_atoi(split[1]) < 0 || ft_atoi(split[1]) > 255 || ft_atoi(split[2]) < 0 || ft_atoi(split[2]) > 255 || ft_atoi(split[3]) < 0 || ft_atoi(split[3]) > 255)
			{
				printf("Error: RGB values out of range (0-255)\n");
				exit(EXIT_FAILURE);
			}
			img->ceiling_color.r = ft_atoi(split[1]);
			img->ceiling_color.g = ft_atoi(split[2]);
			img->ceiling_color.b = ft_atoi(split[3]);
		}
	}
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/**
 * @brief 
 * A função is_texture_or_color_line() verifica se uma linha de entrada contém informações sobre
 * uma textura (Norte, Sul, Oeste, Leste) ou uma cor (Piso ou Teto) em um arquivo de configuração do jogo.
 * Se a linha contiver informações sobre uma textura, ela chama a função parse_texture_line() para processar
 * e armazenar as informações da textura na estrutura t_texture. Se a linha contiver informações sobre uma cor,
 * ela chama a função parse_color_line() para processar e armazenar as informações da cor na estrutura t_img.
 *
 * @param cub um ponteiro para uma estrutura t_cub que contém informações relacionadas ao jogo.
 * @param str uma string contendo a linha de entrada que será verificada.
 * 
 * @return 1 se a linha contiver informações sobre uma textura ou uma cor, caso contrário, retorna 0.
 */
int	is_texture_or_color_line(t_cub *cub, char *str)
{
	if (ft_strnstr(str, "NO ", ft_strlen(str)) != NULL || \
	ft_strnstr(str, "SO ", ft_strlen(str)) != NULL || \
	ft_strnstr(str, "WE ", ft_strlen(str)) != NULL || \
	ft_strnstr(str, "EA ", ft_strlen(str)) != NULL)
	{
		parse_texture_line(str, &(cub->texture));
		return (1);
	}
	else if (ft_strnstr(str, "F ", ft_strlen(str)) != NULL || \
	ft_strnstr(str, "C ", ft_strlen(str)) != NULL)
	{
		parse_color_line(str, &(cub->img));
		return (1);
	}
	return (0);
}

/**
 * @brief 
 * A função is_map_line() verifica se uma linha de entrada contém informações 
 * válidas de um mapa em um arquivo
 * de configuração do jogo. Isso inclui caracteres como espaço, 'N', 'S', 'W', 'E', '1' e '0'.
 *
 * @param str uma string contendo a linha de entrada que será verificada.
 * 
 * @return 1 se a linha contiver informações válidas de um mapa, caso contrário, retorna 0.
 */
int	is_map_line(char *str)
{
	while (*str)
	{
		if (*str == ' ' || *str == 'N' || *str == 'S' || \
		 *str == 'W' || *str == 'E' || *str == '1' || \
		 *str == '0')
			return (1);
		str++;
	}
	return (0);
}

/**
 * @brief 
 * A função parse_texture_line() analisa uma linha de entrada que contém informações sobre uma textura
 * (Norte, Sul, Oeste, Leste) em um arquivo de configuração do jogo. Ela divide a linha em partes com
 * base nos espaços em branco e, em seguida, extrai o caminho da textura e o armazena na estrutura t_texture
 * fornecida.
 *
 * @param str uma string contendo a linha de entrada que contém informações sobre uma textura.
 * @param texture um ponteiro para uma estrutura t_texture que será atualizada com as informações da textura.
 * 
 * @return Esta função não retorna um valor.
 */
void	parse_texture_line(char *str, t_texture *texture)
{
	char	**split;
	size_t	i;
	size_t	len;

	printf("\n\nIN PARSE_TEXTURE_LINE\n");

	i = 0;
	split = ft_split(str, ' ');
	if (!split)
	{
		printf(ERROR_MEMORY);
		exit(EXIT_FAILURE);
	}
	if (split[0] && split[1])
	{
		//imprime o último caractere de split[1]
		printf("split[1]: %s\n", split[1]);
		printf("split[1][ft_strlen(split[1]) - 1]: %c\n", split[1][ft_strlen(split[1]) - 1]);
		printf("split[1][ft_strlen(split[1]) - 1]: %d\n", split[1][ft_strlen(split[1]) - 1]);
		len = ft_strlen(split[1]);
		if (len > 0 && split[1][len - 1] == '\n')
			split[1][len - 1] = '\0';
		if (ft_strnstr(str, "NO ", ft_strlen(str)) != NULL)
			texture->north.path = ft_strdup(split[1]);
		else if (ft_strnstr(str, "SO ", ft_strlen(str)) != NULL)
			texture->south.path = ft_strdup(split[1]);
		else if (ft_strnstr(str, "WE ", ft_strlen(str)) != NULL)
			texture->west.path = ft_strdup(split[1]);
		else if (ft_strnstr(str, "EA ", ft_strlen(str)) != NULL)
			texture->east.path = ft_strdup(split[1]);
	}
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	printf("texture->north.path: %s\n", texture->north.path);
	//imprimir o ultimo caractere de texture->north.path
	printf("texture->north.path: %c\n", texture->north.path[ft_strlen(texture->north.path) - 1]);
	printf("last char of texture->north.path: %d\n", texture->north.path[ft_strlen(texture->north.path) - 1]);
	printf("texture->north.height: %d\n", texture->north.height);
	printf("texture->north.width: %d\n", texture->north.width);

	printf("\n\nOUT PARSE_TEXTURE_LINE\n");
}



/**
** @brief A função parse_map_line() adiciona uma nova linha ao mapa armazenado em
** cub->map->map_lines. Ela verifica se a linha passada é válida para ser uma
** linha do mapa. Se a linha for válida, a função aloca espaço para a nova linha,
** copia as linhas já existentes para a nova matriz, adiciona a nova linha e
** incrementa a altura do mapa.
**
** @param cub um ponteiro para a estrutura t_cub que contém o mapa e outras
**   informações relacionadas.
**  @param str uma string contendo a linha do mapa a ser adicionada.
**
** @return
** Esta função não retorna um valor.
**
*/
void	parse_map_line(t_cub *cub, char *str)
{
	char	**new_map_lines;
	size_t	i;

	// Verifica se é uma linha válida do mapa
	if (!is_empty_or_spaces(str) && is_map_line(str))
	{
		// Aloca espaço para uma nova linha do mapa
		new_map_lines = ft_calloc(cub->map->height + 1, sizeof(char *));
		if (!new_map_lines)
		{
			printf(ERROR_MEMORY);
			exit(EXIT_FAILURE);
		}
		// Copia as linhas já existentes para a nova matriz
		i = 0;
		while (i < cub->map->height)
		{
			new_map_lines[i] = cub->map->map_lines[i];
			i++;
		}
		// Libera a matriz antiga, se existir
		free(cub->map->map_lines);
		cub->map->map_lines = new_map_lines;
		// Aloca espaço para a nova linha e a adiciona ao final da matriz
		cub->map->map_lines[cub->map->height] = ft_strdup(str);
		if (!cub->map->map_lines[cub->map->height])
		{
			printf(ERROR_MEMORY);
			exit(EXIT_FAILURE);
		}
		cub->map->height++;
	}
}

/**
 * @brief 
 * A função parse_map_file_lines() percorre cada linha do mapa armazenado em
 * cub->map->map_file. Para cada linha, verifica se não está vazia ou composta
 * apenas por espaços. Se a linha for uma linha de textura ou cor, é processada
 * de acordo. Se a linha for uma linha do mapa, é analisada e processada
 * utilizando a função parse_map_line(). Informações sobre as cores do piso e do
 * teto são impressas para depuração.
 *
 * @param
 * - cub: um ponteiro para a estrutura t_cub que contém o mapa e informações
 *   relacionadas, como texturas e cores.
 *
 * @return
 * Esta função não retorna um valor.
 *
*/
void	parse_map_file_lines(t_cub *cub)
{
			printf("\n\nIN READ_CUB_MAP_FILE\n");
	size_t	i;
	i = 0;
	while (cub->map->map_file[i])
	{
		if (!is_empty_or_spaces(cub->map->map_file[i]))
		{
			if (!is_texture_or_color_line(cub, cub->map->map_file[i]) && is_map_line(cub->map->map_file[i]))
			{
				parse_map_line(cub, cub->map->map_file[i]);
			}
		}
		i++;
	}
			printf("\n\n-----------------------------\n");
			printf("\n\nREAD_CUB_MAP_FILE\n");
			printf("img->floor_color.r: %d\n", cub->img.floor_color.r);
			printf("img->floor_color.g: %d\n", cub->img.floor_color.g);
			printf("img->floor_color.b: %d\n", cub->img.floor_color.b);
			printf("img->ceiling_color.r: %d\n", cub->img.ceiling_color.r);
			printf("img->ceiling_color.g: %d\n", cub->img.ceiling_color.g);
			printf("img->ceiling_color.b: %d\n", cub->img.ceiling_color.b);
			printf("\n\n-----------------------------\n");

			printf("\n\nOUT READ_CUB_MAP_FILE\n");
}

/**
 * @brief 
 * A função parser_cub() é responsável por realizar o parsing completo do arquivo de configuração do jogo (CUB).
 * Isso inclui a alocação de memória para armazenar as linhas do mapa, o parsing das linhas do mapa usando a função
 * parse_map_file_lines(), a verificação de caracteres válidos no mapa usando a função check_chars(), e a verificação
 * se as paredes do mapa estão totalmente rodeadas por paredes usando a função is_surrounded_walls().
 *
 * @param cub um ponteiro para uma estrutura t_cub que contém informações relacionadas ao jogo.
 * 
 * @return 0 se o parsing for concluído com sucesso, caso contrário, retorna 1.
 */
int	parser_cub(t_cub *cub)
{
			printf("\n\nIN PARSER_CUB\n");

	cub->map->map_lines = ft_calloc(cub->map->height + 1, sizeof(char *));
	if (!cub->map->map_lines)
		return (1);
	
	printf("tudo certo até aqui");
		
	parse_map_file_lines(cub);
	printf("tudo certo até aqui2");
	if (check_chars(cub))
		return (1);

	if (is_surrounded_walls(cub)) 	// is_surrounded_walls não está perfeita
		return (1);

	printf("\n\nOUT PARSER_CUB\n");
	return (0);
}