/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 19:28:37 by joe               #+#    #+#             */
/*   Updated: 2024/06/12 16:50:46 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

#define MINIMAP_SCALE 10 // Nova escala para o minimapa

void set_pos(t_coord *pos, int x, int y)
{
    pos->x = x;
    pos->y = y;
}

static int case_color(t_cub *cub, int x, int y)
{
    char c;

    c = cub->scene_map[y][x];
    if (c == '1' || c == '2')
        return (0x0);
    else if (y == (int)cub->p.y && x == (int)cub->p.x)
        return (0x10CC10);
    else if (c == 'A')
        return (0xCCCCCC);
    return (0xFFFFFF);
}

static void draw_minimap(t_cub *cub, t_coord *start, t_coord *end)
{
    int i;
    int j;
    int color;

    i = 0;
    while (i < cub->map_height)
    {
        j = 0;
        while (j < cub->map_width)
        {
            color = case_color(cub, j, i);
            if (color >= 0)
            {
                set_pos(start, WIN_WIDTH - (cub->map_width * MINIMAP_SCALE) - 5 + (j * MINIMAP_SCALE),
                        WIN_HEIGHT - (cub->map_height * MINIMAP_SCALE) - 5 + (i * MINIMAP_SCALE));
                set_pos(end, WIN_WIDTH - (cub->map_width * MINIMAP_SCALE) + (j * MINIMAP_SCALE),
                        WIN_HEIGHT - (cub->map_height * MINIMAP_SCALE) + (i * MINIMAP_SCALE));
                draw_rectangle(cub, *start, *end, color);
            }
            j++;
        }
        i++;
    }
}

void 	render_mini_map (t_cub *cub)
{
    t_coord start;
    t_coord end;

    set_pos(&start, 2, WIN_HEIGHT - 27);
    set_pos(&end, 210, WIN_HEIGHT - 2);
    draw_rectangle(cub, start, end, 0xFFFFFF);
    draw_minimap(cub, &start, &end);
}

