/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_get_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evdos-sa <evdos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:37:01 by evdos-sa          #+#    #+#             */
/*   Updated: 2024/06/19 15:59:35 by evdos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_char(const char *str, char ch)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == ch)
			count++;
		str++;
	}
	return (count);
}

static bool	validate_line_conditions(const char *line)
{
	int	comma_count;
	int	negative_count;

	if (!line)
		return (false);
	comma_count = count_char(line, ',');
	negative_count = count_char(line, '-');
	if (comma_count != 2)
		return (false);
	if (negative_count % 2 != 0)
		return (false);
	return (true);
}

static int	validate_component(char *line, t_get_color *c, \
int *color, int shift)
{
	char	*comma_pos;

	if (!line || !c || !color)
		return (-1);
	comma_pos = ft_strchr(line + c->start, ',');
	if (!comma_pos && shift != 0)
		return (-1);
	if (comma_pos)
		c->len = comma_pos - (line + c->start);
	else
		c->len = ft_strlen(line + c->start);
	c->temp[shift / 8] = ft_substr(line, c->start, c->len);
	if (!c->temp[shift / 8] || ft_strlen(c->temp[shift / 8]) \
	<= 0 || ft_atoi(c->temp[shift / 8]) > 255)
		return (-1);
	*color |= ((unsigned char) ft_atoi(c->temp[shift / 8])) << shift;
	c->start += c->len + 1;
	return (0);
}

static void	free_components(t_get_color *c)
{
	if (c)
	{
		free_ptr(&c->temp[0]);
		free_ptr(&c->temp[1]);
		free_ptr(&c->temp[2]);
	}
}

/**
 * @brief
 * A função get_color() converte uma string que representa
 * uma cor no formato "R,G,B"
 * em um valor inteiro, preenchendo o valor no ponteiro fornecido.
 *
 * @param color Um ponteiro para o inteiro que armazenará a cor
 * resultante no formato 0xRRGGBB.
 * @param line A linha contendo a definição da cor no formato "R,G,B".
 *
 * @return Um inteiro indicando sucesso (1) ou falha (-1)
 * no processamento da cor.
 */
int	get_color(int *color, char *line)
{
	t_get_color	c;

	if (!color || !line)
		return (-1);
	if (!validate_line_conditions(line))
		return (-1);
	ft_bzero(&c, sizeof(t_get_color));
	c.ret = 1;
	c.start = 2;
	if (validate_component(line, &c, color, 16) == -1)
		return (free_components(&c), -1);
	if (validate_component(line, &c, color, 8) == -1)
		return (free_components(&c), -1);
	if (validate_component(line, &c, color, 0) == -1)
		return (free_components(&c), -1);
	if (!c.temp[0] || !c.temp[1] || !c.temp[2])
		c.ret = -1;
	free_components(&c);
	return (c.ret);
}
