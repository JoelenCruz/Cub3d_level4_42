/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 11:18:39 by joe               #+#    #+#             */
/*   Updated: 2024/04/06 13:45:53 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			// printf("LINE: %s\n", line);
			temp = ft_calloc(i + 2, sizeof(char *)); // Aloca um novo array temporário
			if (!temp)
			{
				printf("Error: memory allocation failed\n");
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

	// printf("\n\n-----------------------------\n");
	// printf("\n\nREAD_MAP_FILE\n");
	// print_read_map_file(cub);
	// printf("\n\n-----------------------------\n");

	printf("\n\nOUT READ_MAP_FILE\n");
}

void	cub_check_args(int argc, char **argv)
{
	printf("\n\nIN CUB_CHECK_ARGS\n");

	if (argc != 2)
	{
		printf("Error\nInvalid number of arguments.\n");
		exit(1);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
	{
		printf("Error\nInvalid file extension.\n");
		exit(1);
	}
	printf("\n\nOUT CUB_CHECK_ARGS\n");
}