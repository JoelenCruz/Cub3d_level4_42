/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evdos-sa <evdos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:02:31 by everton           #+#    #+#             */
/*   Updated: 2024/06/22 09:30:49 by evdos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief
 * A função cub_check_args() verifica se o número correto de argumentos foi
 * passado ao programa e se o argumento fornecido possui a extensão ".cub".
 * Se o número de argumentos não for 2 ou se a extensão do arquivo não for
 ".cub",
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
	if (argc != 2)
	{
		printf(ERROR_NUMB_ARG);
		printf(ERROR_TRY_ARG);
		exit(1);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
	{
		printf(ERROR_EXTENSION);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	cub_check_args(argc, argv);
	cub_init(&cub, argv);
	cub_run(&cub);
	return (0);
}
