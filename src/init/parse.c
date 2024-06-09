/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:23:54 by joe               #+#    #+#             */
/*   Updated: 2024/06/09 16:47:00 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

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


static int	get_color(int *color, char *line)
{
	t_get_color	c;

	ft_bzero (&c, sizeof (t_get_color));
	c.ret = 1;
	c.start = 2;
	c.len = ft_strchr (line + c.start, ',') - line - c.start;
	c.temp[0] = ft_substr (line, c.start, c.len);
	*color = ft_atoi (c.temp[0]) << 16;
	c.start += c.len + 1;
	c.len = ft_strchr (line + c.start, ',') - line - c.start;
	c.temp[1] = ft_substr (line, c.start, c.len);
	*color |= ((unsigned char) ft_atoi (c.temp[1])) << 8;
	c.start += c.len + 1;
	c.len = ft_strchr (line + c.start, '\0') - line - c.start;
	c.temp[2] = ft_substr (line, c.start, c.len);
	*color |= ((unsigned char) ft_atoi (c.temp[2]));
	if (!c.temp[0] || !c.temp[1] || !c.temp[2])
		c.ret = -1;
	free_ptr (&c.temp[0]);
	free_ptr (&c.temp[1]);
	free_ptr (&c.temp[2]);
	return (c.ret);
}

static int	set_data(t_cub *cub, char *line)
{
	size_t		len;
	int			ret;
	static int	start;

	len = 0;
	ret = 0;
	while (line[len] && line[len] != '\n')
		len++;
	if (!ft_strncmp (line, "NO ", 3) && !start)
		cub -> texture.north_file = ft_strtrim(line, "NO \n\r");
	else if (!ft_strncmp (line, "SO ", 3) && !start)
		cub -> texture.south_file = ft_strtrim(line, "SO \n\r");
	else if (!ft_strncmp (line, "WE ", 3) && !start)
		cub -> texture.west_file = ft_strtrim(line, "WE \n\r");
	else if (!ft_strncmp (line, "EA ", 3) && !start)
		cub -> texture.east_file = ft_strtrim(line, "EA \n\r");
	else if (!ft_strncmp (line, "F ", 2) && !start)
		ret = get_color (&cub -> colors.floor, line);
	else if (!ft_strncmp (line, "C ", 2) && !start)
		ret = get_color (&cub -> colors.ceiling, line);
	else if (ft_strchr("NWES01 ", line[0]) || start)
		start = get_map (cub, line);
	return (ret);
}

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