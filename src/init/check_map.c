/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 11:18:39 by joe               #+#    #+#             */
/*   Updated: 2024/06/02 14:33:15 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


/**
 * @brief Leitura de um arquivo de mapa linha por linha.A função read_map_file() 
 * abre e lê um arquivo de mapa especificado por
 * filename, linha por linha. Linhas que não são vazias ou que não são compostas
 * apenas por espaços são armazenadas no membro map_file da estrutura cub->map.
 * Em caso de falha ao abrir o arquivo ou alocar memória, a função imprime uma
 * mensagem de erro e termina o programa.
 * @param 
 * - cub: um ponteiro para a estrutura t_cub que contém o mapa.
 * @param 
 * - filename: uma string representando o nome do arquivo a ser lido.
 * @return não retorna valor 
 */
void	read_map_file(t_cub *cub, char *filename)
{
	int		fd;
	char	*line;
	char	**temp;
	size_t	i;

		printf("\n\nIN READ_MAP_FILE\n");

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: failed to open file %s\n", filename);
		exit(EXIT_FAILURE);
	}

	cub->map->map_file = ft_calloc(1, sizeof(char *));
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (!is_empty_or_spaces(line) && line[0] != '\n')
		{
			temp = ft_calloc(i + 2, sizeof(char *)); // Aloca um novo array temporário
			if (!temp)
			{
				printf(ERROR_MEMORY);
				exit(EXIT_FAILURE);
			}
			ft_memcpy(temp, cub->map->map_file, i * sizeof(char *)); // Copia os ponteiros existentes
			free(cub->map->map_file); // Libera a memória alocada anteriormente
			cub->map->map_file = temp; // Atribui o novo array
			cub->map->map_file[i] = ft_strdup(line); // Aloca e copia a linha atual
			i++;
		}
		free(line);
	}
	close(fd);

		printf("\n\nOUT READ_MAP_FILE\n");
}

/**
 * @brief
 * A função cub_check_args() verifica se o número correto de argumentos foi 
 * passado ao programa e se o argumento fornecido possui a extensão ".cub".
 * Se o número de argumentos não for 2 ou se a extensão do arquivo não for ".cub",
 * a função imprime uma mensagem de erro apropriada e termina o programa.
 *
 * @param
 * - argc: o número de argumentos passados ao programa.
 * @param
 * - argv: uma matriz de strings contendo os argumentos passados ao programa.
 *
 * @return
 * Esta função não retorna um valor.
 *
*/
void	cub_check_args(int argc, char **argv)
{
			printf("\n\nIN CUB_CHECK_ARGS\n");

	if (argc != 2)
	{
		printf(ERROR_NUMB_ARG);
		exit(1);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
	{
		printf(ERROR_EXTENSION);
		exit(1);
	}
			printf("\n\nOUT CUB_CHECK_ARGS\n");
}