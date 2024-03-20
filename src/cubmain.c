/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubmain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: everton <everton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:02:31 by everton           #+#    #+#             */
/*   Updated: 2024/03/19 19:24:18 by everton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// .C
#include "cub3d.h"

int	is_empty_or_spaces(char *str);

void	print_read_map_file(t_cub *cub)
{
	// printf("\n\nIN PRINT_READ_MAP_FILE\n");
	size_t	i;

	i = 0;
	while (cub->map->map_file[i])
	{
		printf("cub->map->map_file[%li]: %s\n", i, cub->map->map_file[i]);
		i++;
	}
	// printf("\n\nOUT PRINT_READ_MAP_FILE\n");
}

void	set_zero(t_cub *cub)
{
	printf("\n\nIN SET_ZERO\n");

	cub->mlx = NULL;
	cub->win = NULL;
	cub->map = ft_calloc(1, sizeof(t_map));
	if (!cub->map)
	{
		printf("Error: memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	cub->map->map_file = NULL;
	cub->map->map_lines = NULL;
	cub->map->start_map = 0;
	cub->map->width = 0;
	cub->map->height = 0;
	cub->img.img = NULL;
	cub->img.path = NULL;
	cub->img.bpp = 0;
	cub->img.line_len = 0;
	cub->img.endian = 0;
	cub->img.width = 0;
	cub->img.height = 0;
	cub->img.floor_color.r = 0;
	cub->img.floor_color.g = 0;
	cub->img.floor_color.b = 0;
	cub->img.ceiling_color.r = 0;
	cub->img.ceiling_color.g = 0;
	cub->img.ceiling_color.b = 0;
	cub->texture.north.img = NULL;
	cub->texture.north.path = NULL;
	cub->texture.south.img = NULL;
	cub->texture.south.path = NULL;
	cub->texture.east.img = NULL;
	cub->texture.east.path = NULL;
	cub->texture.west.img = NULL;
	cub->texture.west.path = NULL;
	cub->player.x = 0;
	cub->player.y = 0;
	cub->player.dir = 0;
	cub->player.dir_x = 0;
	cub->player.dir_y = 0;

	printf("\n\nOUT SET_ZERO\n");
}

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
		printf("Error: memory allocation failed\n");
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


void	parse_color_line(char *str, t_img *img)
{
	char	**split;
	size_t	i;

	i = 0;
	split = ft_split(str, ' ');
	if (!split)
	{
		printf("Error: memory allocation failed\n");
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
			printf("Error: memory allocation failed\n");
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
			printf("Error: memory allocation failed\n");
			exit(EXIT_FAILURE);
		}
		cub->map->height++;
	}
}

void	read_cub_map_file(t_cub *cub)
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
	// printf("\n\n-----------------------------\n");
	// printf("\n\nREAD_CUB_MAP_FILE\n");
	// printf("img->floor_color.r: %d\n", cub->img.floor_color.r);
	// printf("img->floor_color.g: %d\n", cub->img.floor_color.g);
	// printf("img->floor_color.b: %d\n", cub->img.floor_color.b);
	// printf("img->ceiling_color.r: %d\n", cub->img.ceiling_color.r);
	// printf("img->ceiling_color.g: %d\n", cub->img.ceiling_color.g);
	// printf("img->ceiling_color.b: %d\n", cub->img.ceiling_color.b);
	// printf("\n\n-----------------------------\n");

	printf("\n\nOUT READ_CUB_MAP_FILE\n");
}

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
				// printf("cub->map->map_lines[%li][%li]: %c\n", i, j, cub->map->map_lines[i][j]);
				// printf("cub->map->map_lines[%li][%li]: %i\n", i, j, cub->map->map_lines[i][j]);
				// printf("Error: invalid character in map\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	is_surrounded_walls(t_cub *cub)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < cub->map->height)
	{
		j = 0;
		while (cub->map->map_lines[i][j])
		{
			if (cub->map->map_lines[i][j] == ' ')
			{
				if ((i == 0 && j == 0) || (i == 0 && j == cub->map->width - 1) ||
					(i == cub->map->height - 1 && j == 0) || (i == cub->map->height - 1 && j == cub->map->width - 1))
				{
					printf("Error: map is not surrounded by walls\n");
					return (1);
				}
				else if (i == 0 || i == cub->map->height - 1 || j == 0 || j == cub->map->width - 1 ||
						 cub->map->map_lines[i - 1][j] == ' ' || cub->map->map_lines[i + 1][j] == ' ' ||
						 cub->map->map_lines[i][j - 1] == ' ' || cub->map->map_lines[i][j + 1] == ' ')
				{
					printf("Error: map is not surrounded by walls\n");
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
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

void	get_direction(t_cub *cub, size_t x, size_t y)
{
	cub->player.x = x + 0.5;
	cub->player.y = y + 0.5;
	if (cub->map->map_lines[y][x] == 'N')
	{
		cub->player.dir = PI / 2;
		cub->player.dir_x = -1;
		cub->player.dir_y = 0;
	}
	else if (cub->map->map_lines[y][x] == 'S')
	{
		cub->player.dir = 3 * PI / 2;
		cub->player.dir_x = 1;
		cub->player.dir_y = 0;
	}
	else if (cub->map->map_lines[y][x] == 'W')
	{
		cub->player.dir = PI;
		cub->player.dir_x = 0;
		cub->player.dir_y = -1;
	}
	else if (cub->map->map_lines[y][x] == 'E')
	{
		cub->player.dir = 0;
		cub->player.dir_x = 0;
		cub->player.dir_y = 1;
	}
}

// A função get_player_info percorre o mapa do jogo e identificar a posição inicial e a direção do jogador, representado por um dos caracteres 'N', 'S', 'W' ou 'E', indicando a direção para a qual o jogador está olhando.
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

void	cub_init(t_cub *cub, char *file)
{
	printf("\n\nIN CUB_INIT\n");

	set_zero(cub);
	read_map_file(cub, file);
	if (parser_cub(cub))
	{
		printf("Error\nInvalid map\n");
		exit(1);
	}
	get_player_info(cub);
	printf("player.x: %f\n", cub->player.x);
	printf("player.y: %f\n", cub->player.y);
	printf("player.dir: %f\n", cub->player.dir);
	printf("player.dir_x: %f\n", cub->player.dir_x);
	printf("player.dir_y: %f\n", cub->player.dir_y);

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

// ------------- mlx ----------------------------------------------

void	draw_pixel(t_cub *cub, int x, int y, t_color color)
{
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		mlx_pixel_put(cub->mlx, cub->win, x, y, (color.r << 16) | (color.g << 8) | color.b);
	}
}

void	load_texture(t_cub *cub, t_img *texture)
{
	printf("\n\nIN LOAD_TEXTURE\n");
	texture->img = mlx_xpm_file_to_image(cub->mlx, texture->path, &texture->width, &texture->height);
	printf("texture->path: %s\n", texture->path);
	printf("texture->height: %d\n", texture->height);
	printf("texture->width: %d\n", texture->width);
	if (!texture->img)
	{
		printf("Error: failed to load texture %s\n", texture->path);
		exit(EXIT_FAILURE);
	}
	texture->data = (int *)mlx_get_data_addr(texture->img, &texture->bpp, &texture->line_len, &texture->endian);
	printf("\n\nOUT LOAD_TEXTURE\n");
}

void	draw_texture(t_cub *cub, t_img *texture, int x, int y)
{
	int tex_x;
	int tex_y;
	int color;

	printf("\n\nIN DRAW_TEXTURE\n");

	tex_x = (int)(cub->map->width * cub->player.x);
	tex_y = (int)(cub->map->height * cub->player.y);

	// Verifica se as coordenadas estão dentro dos limites da janela
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		color = texture->data[tex_y * texture->width + tex_x];
		mlx_pixel_put(cub->mlx, cub->win, x, y, color);
	}

	printf("\n\nOUT DRAW_TEXTURE\n");
}

// Função para desenhar as texturas na tela
void	render_textures(t_cub *cub)
{
	printf("\n\nIN RENDER_TEXTURES\n");

	// printf("cub->texture.north.path: %s\n", cub->texture.north.path);
	// printf("cub->texture.north.height: %d\n", cub->texture.north.height);
	// printf("cub->texture.north.width: %d\n", cub->texture.north.width);
	// Carrega as texturas
	load_texture(cub, &(cub->texture.north));
	load_texture(cub, &(cub->texture.south));
	load_texture(cub, &(cub->texture.east));
	load_texture(cub, &(cub->texture.west));

	printf("chegamos aqui !\n");

	// Desenha as texturas na tela
	draw_texture(cub, &(cub->texture.north), 0, 0);
	draw_texture(cub, &(cub->texture.south), 0, WIN_HEIGHT / 2);
	draw_texture(cub, &(cub->texture.east), WIN_WIDTH / 2, 0);
	draw_texture(cub, &(cub->texture.west), WIN_WIDTH / 2, WIN_HEIGHT / 2);

	// Libera a memória alocada para as texturas
	mlx_destroy_image(cub->mlx, cub->texture.north.img);
	mlx_destroy_image(cub->mlx, cub->texture.south.img);
	mlx_destroy_image(cub->mlx, cub->texture.east.img);
	mlx_destroy_image(cub->mlx, cub->texture.west.img);

	printf("\n\nOUT RENDER_TEXTURES\n");
}

void render_frame(t_cub *cub)
{
	int	y;
	int	x;

	y = 0;
	// Preenche a metade superior da tela com a cor do teto
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			draw_pixel(cub, x, y, cub->img.ceiling_color);
			x++;
		}
		y++;
	}

	// Preenche a metade inferior da tela com a cor do chão
	y = WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			draw_pixel(cub, x, y, cub->img.floor_color);
			x++;
		}
		y++;
	}
	render_textures(cub);
}

// Função que inicia o jogo
void	cub_start(t_cub *cub)
{
	printf("\n\nIN CUB_START\n");

	cub->mlx = mlx_init();
	if (!cub->mlx)
	{
		printf("Error: mlx_init failed\n");
		exit(EXIT_FAILURE);
	}
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!cub->win)
	{
		printf("Error: mlx_new_window failed\n");
		exit(EXIT_FAILURE);
	}
	render_frame(cub);
	mlx_loop(cub->mlx);

	printf("\n\nOUT CUB_START\n");
}

// ------------- mlx ----------------------------------------------


int	main(int argc, char **argv)
{
	t_cub	cub;

	cub_check_args(argc, argv);
	cub_init(&cub, argv[1]);

	printf("\n-----------------------------------");
	printf("\n\nMAIN\n");

	printf("\n\nmap_file\n\n");
	if (cub.map->map_file != NULL)
		print_read_map_file(&cub);

	printf("\n\ntexture path\n\n");
	printf("NORTH: %s\n", cub.texture.north.path);
	printf("SOUTH: %s\n", cub.texture.south.path);
	printf("WEST: %s\n", cub.texture.west.path);
	printf("EAST: %s\n", cub.texture.east.path);

	printf("\n\nRGB\n\n");
	printf("img->floor_color.r: %d\n", cub.img.floor_color.r);
	printf("img->floor_color.g: %d\n", cub.img.floor_color.g);
	printf("img->floor_color.b: %d\n", cub.img.floor_color.b);
	printf("img->ceiling_color.r: %d\n", cub.img.ceiling_color.r);
	printf("img->ceiling_color.g: %d\n", cub.img.ceiling_color.g);
	printf("img->ceiling_color.b: %d\n", cub.img.ceiling_color.b);

	printf("\n\ncolor path\n\n");
	printf("FLOOR: %d %d %d\n", cub.img.floor_color.r, cub.img.floor_color.g, cub.img.floor_color.b);
	printf("CEILING: %d %d %d\n", cub.img.ceiling_color.r, cub.img.ceiling_color.g, cub.img.ceiling_color.b);

	printf("\n\nmap_lines\n\n");
	if (cub.map->map_lines != NULL)
		print_read_map_lines(&cub);
	printf("\n-----------------------------------\n");

	cub_start(&cub);
	return (0);
}
