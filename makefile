# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: everton <everton@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/14 18:17:27 by everton           #+#    #+#              #
#    Updated: 2024/03/15 13:20:28 by everton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --------------------------------------------------------- #
# MAKEFILE FOR CUB3D
# --------------------------------------------------------- #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = cub3D

SRC_DIR = src
INCLUDE_DIR = includes
OBJ_DIR = obj

# Adicione o diretório libft
LIBFT_DIR = libft
LIBFT_SRCS = $(wildcard $(LIBFT_DIR)/*.c)
LIBFT_OBJS = $(patsubst $(LIBFT_DIR)/%.c,$(OBJ_DIR)/%.o,$(LIBFT_SRCS))

# Adicione o diretório minilibx_linux
MINILIBX_DIR = minilibx_linux

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lreadline -L$(LIBFT_DIR) -lft -L$(MINILIBX_DIR) -lmlx -lX11 -lXext -lm

# Regra para compilar os arquivos de objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(MINILIBX_DIR) -o $@ -c $<

# Regra para compilar os arquivos da libft
$(OBJ_DIR)/%.o: $(LIBFT_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $@ -c $<

clean:
	rm -f $(OBJS) $(LIBFT_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
