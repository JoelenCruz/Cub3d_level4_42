/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: everton <everton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:23:54 by joe               #+#    #+#             */
/*   Updated: 2024/06/21 19:38:02 by everton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief
 * A função get_map() adiciona uma linha do mapa à estrutura t_cub,
 * atualizando a altura e largura do mapa conforme necessário.
 *
 * @param cub Um ponteiro para a estrutura t_cub que
 * contém as informações do mapa.
 * @param line A linha do mapa a ser adicionada.
 *
 * @return Sempre retorna 1, indicando que o processamento do mapa
 * começou ou continua.
 */
int	get_map(t_cub *cub, char *line)
{
	char	**temp;
	int		i;

	cub -> map_height++;
	temp = ft_calloc (cub -> map_height + 1, sizeof (char *));
	if (!temp)
		cub_exit (cub, "Can't allocate memory.", 1);
	i = 0;
	while (cub -> scene_map && cub -> scene_map[i])
	{
		temp[i] = ft_strdup (cub -> scene_map[i]);
		i++;
	}
	if (cub -> map_width < (int) ft_strlen (line))
		cub -> map_width = (int) ft_strlen (line);
	temp[i] = ft_strdup (line);
	free_mat (&cub -> scene_map);
	cub -> scene_map = temp;
	return (1);
}

/**
 * @brief
 * A função set_data() processa uma linha do arquivo de descrição da cena
 * e preenche a estrutura t_cub com as informações apropriadas.
 *
 * @param cub Um ponteiro para a estrutura t_cub que será preenchida
 * com os dados da cena.
 * @param line A linha de dados a ser processada.
 *
 * @return Um inteiro indicando sucesso (0) ou falha
 * (número positivo indicando o erro).
 */
static int	set_data(t_cub *cub, char *line)
{
	size_t		len;
	int			ret;
	static int	start;

	len = 0;
	ret = 0;
	while (line[len] && (line[len] == ' ' || line[len] == '\t'))
		len++;
	if (!ft_strncmp(line + len, "NO ", 3) && !start)
		cub->texture.north_file = ft_strtrim(line + len, "NO \n\r");
	else if (!ft_strncmp(line + len, "SO ", 3) && !start)
		cub->texture.south_file = ft_strtrim(line + len, "SO \n\r");
	else if (!ft_strncmp(line + len, "WE ", 3) && !start)
		cub->texture.west_file = ft_strtrim(line + len, "WE \n\r");
	else if (!ft_strncmp(line + len, "EA ", 3) && !start)
		cub->texture.east_file = ft_strtrim(line + len, "EA \n\r");
	else if (!ft_strncmp(line + len, "F ", 2) && !start)
		ret = get_color(&cub->colors.floor, line + len);
	else if (!ft_strncmp(line + len, "C ", 2) && !start)
		ret = get_color(&cub->colors.ceiling, line + len);
	else if (ft_strchr("NWES01 ", line[len]) || start)
		start = get_map(cub, line + (len - len));
	return (ret);
}

/**
 * @brief
 * A função get_scene_description_data() lê os dados da cena a partir
 * do arquivo de descrição e preenche a estrutura t_cub com essas
 * informações.
 *
 * @param cub Um ponteiro para a estrutura t_cub que contém o nome do
 * arquivo de descrição da cena e onde os dados serão armazenados.
 *
 * @return Esta função não retorna um valor.
 */
void	get_scene_description_data(t_cub *cub)
{
	char	*line;
	int		fd;
	int		error;

	fd = open (cub -> scene_description, O_RDONLY);
	if (fd == -1)
		cub_exit (cub, "Can't open scene description file.", 1);
	line = get_next_line (fd);
	error = 0;
	while (line && error >= 0)
	{
		error += set_data (cub, line);
		free_ptr (&line);
		line = get_next_line (fd);
	}
	if (error < 2)
	{
		while (line)
		{
			free_ptr (&line);
			line = get_next_line (fd);
		}
	}
	if (error < 2)
		cub_exit (cub, "Invalid scene information.", 1);
}
