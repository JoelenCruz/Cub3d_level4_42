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

#define MINIMAP_SCALE 7 // escala para o minimapa


// // Função para desenhar texto simples na janela usando MiniLibX
// void draw_text(void *mlx_ptr, void *win_ptr, int x, int y, char *text, int color)
// {
//     int i;
//     int char_width;
//     int char_height;
//     int char_spacing;

//     i = 0;
//     char_width = 10; // Largura aproximada de cada caractere
//     char_height = 20; // Altura aproximada de cada caractere
//     char_spacing = 1; // Espaçamento entre caracteres

//     // Ajuste de cor para a MiniLibX
//     int mlx_color = (color & 0xFF0000) >> 16 | (color & 0x00FF00) | (color & 0x0000FF) << 16;

//     while (text[i])
//     {
//         char c = text[i];
//         int char_x = x + i * (char_width + char_spacing);
//         int char_y = y;

//         // Desenha o caractere atual na posição apropriada
//         if (c >= ' ' && c <= '~') // Apenas desenha caracteres visíveis
//         {
//             mlx_string_put(mlx_ptr, win_ptr, char_x, char_y, mlx_color, &c);
//         }

//         i++;
//     }
// }



/**
 * @brief Define a posição de uma coordenada.
 *
 * Esta função define os valores x e y da estrutura t_coord 
 * para as coordenadas especificadas.
 *
 * @param pos Ponteiro para a estrutura t_coord cujos 
 * valores de posição serão definidos.
 * @param x Valor da coordenada x a ser definido.
 * @param y Valor da coordenada y a ser definido.
 */
void set_pos(t_coord *pos, int x, int y)
{
    pos->x = x;
    pos->y = y;
}

/**
 * @brief Retorna uma cor baseada no valor do caractere na posição (x, y) 
 * do mapa da cena.
 *
 * Esta função verifica o caractere presente no mapa da cena 
 * nas coordenadas (x, y) e retorna uma cor em formato 
 * hexadecimal correspondente ao valor do caractere.
 *
 * @param cub Ponteiro para a estrutura t_cub que contém o 
 * mapa da cena e a posição do jogador.
 * @param x Coordenada x no mapa da cena.
 * @param y Coordenada y no mapa da cena.
 * @return Cor em formato hexadecimal correspondente 
 * ao valor do caractere na posição (x, y).
 */
static int case_color(t_cub *cub, int x, int y)
{
    char c;

    c = cub->scene_map[y][x];
    if (c == '1')
        return (0x000000);  // Preto
    else if (y == (int)cub->p.y && x == (int)cub->p.x)
        return (0xFF0000);  // Vermelho
    else if (c == '0')
        return (0xFFFFFF);      // Branco
    return (-1);
}


/**
 * @brief Desenha um minimapa na janela do jogo.
 *
 * Esta função desenha um minimapa na janela do jogo 
 * com base no mapa da cena armazenado na estrutura t_cub.
 * O minimapa é desenhado a partir das coordenadas de início e fim especificadas.
 *
 * @param cub Ponteiro para a estrutura t_cub que contém o mapa da cena, 
 * altura e largura do mapa.
 * @param start Ponteiro para a estrutura t_coord usada para definir a posição 
 * inicial de um retângulo no minimapa.
 * @param end Ponteiro para a estrutura t_coord usada para definir 
 * a posição final de um retângulo no minimapa.
 */
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

/**
 * @brief Renderiza o minimapa na janela do jogo.
 *
 * Esta função configura as coordenadas de início e fim 
 * para o retângulo do minimapa e chama a função
 * draw_rectangle para desenhar o fundo branco do minimapa. 
 * Em seguida, chama draw_minimap para desenhar
 * o conteúdo do minimapa com base no mapa da cena.
 *
 * @param cub Ponteiro para a estrutura t_cub que contém o mapa da cena 
 * e outras informações necessárias para desenhar o minimapa.
 */
void 	render_mini_map (t_cub *cub)
{
    t_coord start;
    t_coord end;

    draw_minimap(cub, &start, &end);
}

