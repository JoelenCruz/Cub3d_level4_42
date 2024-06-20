/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: everton <everton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:02:31 by everton           #+#    #+#             */
/*   Updated: 2024/06/20 21:57:51 by everton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	cub_screenshot(int fd)
// {
// 	ft_putstr_fd("IN cub_screenshot!\n", 1);

// 	ft_putstr_fd("WIN_WIDTH: ", fd);
// 	ft_putnbr_fd(WIN_WIDTH, fd);
// 	ft_putstr_fd("\n", fd);
// 	ft_putstr_fd("WIN_HEIGHT: ", fd);
// 	ft_putnbr_fd(WIN_HEIGHT, fd);
// 	ft_putstr_fd("\n", fd);

// 	// Falta copiar as linhas do arquivo ".cub" para o arquivo de saída. Ainda não sei se é isso que tem que fazer.



// 	ft_putstr_fd("OUT cub_screenshot!\n", 1);
// }

// static int	render_to_save(t_cub *cub)
// {
// 	check_keys (cub);
// 	draw_background(cub);
// 	raycast (cub);
// 	render_mini_map(cub);
// 	// mlx_put_image_to_window (cub -> mlx, cub -> win, cub -> img.info, 0, 0);
// 	return (0);
// }

// void	cub_save(t_cub *cub)
// {
// 	int	fd;

// 	ft_putstr_fd("IN cub_save!\n", 1);

// 	mlx_loop_hook (cub -> mlx, render_to_save, cub);
// 	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (fd < 0)
// 	{
// 		printf(ERROR_SAVE_FILE);
// 		exit(1);
// 	}
// 	cub_screenshot(fd);
// 	close(fd);
// 	ft_putstr_fd("OUT cub_save!\n", 1);
// 	cub_close(cub);
// }

// int	check_extension(int argc, char **argv, t_cub *cub)
// {
// 	ft_putstr_fd("IN check_extension!\n", 1);
// 	if (argc == 2)
// 	{
// 		if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
// 		{
// 			printf(ERROR_EXTENSION);
// 			exit(1);
// 		}
// 		cub_init(cub, argv);
// 	}
// 	ft_putstr_fd("OUT check_extension!\n", 1);
// 	return (0);
// }

// // ./cub3D maps/good/42.cub --save
// void	new_cub_check_args(int argc, char **argv, t_cub *cub)
// {
// 	if (argc < 2 || argc > 3)
// 	{
// 		ft_putstr_fd("AQUI 1!", 1);
// 		printf(ERROR_NUMB_ARG);
// 		exit(1);
// 	}
// 	ft_putstr_fd("AQUI 2!\n", 1);
// 	cub->save = 0;

// 	ft_putstr_fd("cub->save: ", 1);
// 	ft_putnbr_fd(cub->save, 1);
// 	ft_putstr_fd("\n", 1);

// 	if (argc == 2)
// 		check_extension(argc, argv, cub);

// 	if (argc == 3)
// 	{
// 		if (ft_strncmp(argv[2], "--save", 6) == 0)// se a string for igual a "--save" retorna 0
// 		{
// 			cub->save = 1;

// 			ft_putstr_fd("AQUI 3!\n", 1);
// 			ft_putstr_fd("cub->save: ", 1);
// 			ft_putnbr_fd(cub->save, 1);
// 			ft_putstr_fd("\n", 1);
// 		}
// 		if (cub->save == 1)
// 		{
// 			ft_putstr_fd("AQUI 4!\n", 1);
// 			cub_init(cub, argv);
// 			cub_save(cub);
// 		}
// 		else
// 		{
// 			printf(ERROR_SAVE_ARG);
// 			exit(1);
// 		}
// 	}
// }

// int	main(int argc, char **argv)
// {
// 	t_cub	cub;

// 	cub_check_args(argc, argv, &cub);
// 	cub_init(&cub, argv);
// 	cub_run(&cub);
// 	return (0);
// }

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
