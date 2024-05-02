#include "cub3d.h"


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

int	is_texture_or_color_line(t_cub *cub, char *str)
{
	if (ft_strnstr(str, "NO ", ft_strlen(str)) != NULL || ft_strnstr(str, "SO ", ft_strlen(str)) != NULL || ft_strnstr(str, "WE ", ft_strlen(str)) != NULL || ft_strnstr(str, "EA ", ft_strlen(str)) != NULL)
	{
		parse_texture_line(str, &(cub->texture));
		return (1);
		// printf("i = %i --- NORTH: %s\n", i, cub->texture.north.path);
		// printf("i = %i --- SOUTH: %s\n", i, cub->texture.south.path);
		// printf("i = %i --- WEST: %s\n", i, cub->texture.west.path);
		// printf("i = %i --- EAST: %s\n", i, cub->texture.east.path);
	}
	else if (ft_strnstr(str, "F ", ft_strlen(str)) != NULL || ft_strnstr(str, "C ", ft_strlen(str)) != NULL)
	{
		parse_color_line(str, &(cub->img));
		return (1);
		// printf("i = %i --- FLOOR: %d\n", i, cub->img.floor);
		// printf("i = %i --- CEILING: %d\n", i, cub->img.ceiling);
	}
	return (0);
}

int	is_texture_or_color(char *str)
{
	if (ft_strnstr(str, "NO ", ft_strlen(str)) != NULL || ft_strnstr(str, "SO ", ft_strlen(str)) != NULL || ft_strnstr(str, "WE ", ft_strlen(str)) != NULL || ft_strnstr(str, "EA ", ft_strlen(str)) != NULL || ft_strnstr(str, "F ", ft_strlen(str)) != NULL || ft_strnstr(str, "C ", ft_strlen(str)) != NULL)
		return (1);
	return (0);
}


int	is_map_line(char *str)
{
	while (*str)
	{
		if (*str == ' ' || *str == 'N' || *str == 'S' || *str == 'W' || *str == 'E' || *str == '1' || *str == '0')
			return (1);
		str++;
	}
	return (0);
}

void	print_read_map_lines(t_cub *cub)
{
	size_t	i;

	// printf("\n\nIN PRINT_READ_MAP_LINES\n");

	i = 0;
	// printf("cub->map->height: %li\n", cub->map->height);
	while (i < cub->map->height)
	{
		printf("cub->map->map_lines[%li]: %s\n", i, cub->map->map_lines[i]);
		i++;
	}
	// printf("\n\nOUT PRINT_READ_MAP_LINES\n");
}


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
		// imprime o último caractere de split[1]
		// printf("split[1]: %s\n", split[1]);
		// printf("split[1][ft_strlen(split[1]) - 1]: %c\n", split[1][ft_strlen(split[1]) - 1]);
		// printf("split[1][ft_strlen(split[1]) - 1]: %d\n", split[1][ft_strlen(split[1]) - 1]);
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
	// printf("texture->north.path: %s\n", texture->north.path);
	// //imprimir o ultimo caractere de texture->north.path
	// printf("texture->north.path: %c\n", texture->north.path[ft_strlen(texture->north.path) - 1]);
	// printf("last char of texture->north.path: %d\n", texture->north.path[ft_strlen(texture->north.path) - 1]);
	// printf("texture->north.height: %d\n", texture->north.height);
	// printf("texture->north.width: %d\n", texture->north.width);

	printf("\n\nOUT PARSE_TEXTURE_LINE\n");
}

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

int	parser_cub(t_cub *cub)
{
	printf("\n\nIN PARSER_CUB\n");

	cub->map->map_lines = ft_calloc(cub->map->height + 1, sizeof(char *));
	if (!cub->map->map_lines)
		return (1);
	read_cub_map_file(cub);

	// printf("\n\n-----------------------------\n");
	// printf("\n\nPARSER_CUB\n");
	// printf("img->floor_color.r: %d\n", cub->img.floor_color.r);
	// printf("img->floor_color.g: %d\n", cub->img.floor_color.g);
	// printf("img->floor_color.b: %d\n", cub->img.floor_color.b);
	// printf("img->ceiling_color.r: %d\n", cub->img.ceiling_color.r);
	// printf("img->ceiling_color.g: %d\n", cub->img.ceiling_color.g);
	// printf("img->ceiling_color.b: %d\n", cub->img.ceiling_color.b);
	// printf("\n\n-----------------------------\n");

	if (check_chars(cub))
		return (1);
	// is_surrounded_walls não está perfeita
	if (is_surrounded_walls(cub))
		return (1);

	printf("\n\nOUT PARSER_CUB\n");
	return (0);
}