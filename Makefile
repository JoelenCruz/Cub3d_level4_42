# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evdos-sa <evdos-sa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/06 12:38:00 by joe               #+#    #+#              #
#    Updated: 2024/06/22 14:17:36 by evdos-sa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		 = cub3D

SRC_DIR		 = src/

HDR_DIR		 = includes/

OBJ_DIR		 = objects/

LFT_DIR	 = libft/

SRC			 = main.c \
			   cub_init.c \
			   cub_init_cub_mlx.c \
			   cub_parse.c \
			   cub_get_color.c \
			   cub_check_map.c \
			   cub_utils.c \
			   cub_exit.c \
			   cub_free.c \
			   cub_actions.c \
			   cub_movement.c \
			   cub_draw_background.c \
			   cub_run.c \
			   cub_raycast_utils.c \
			   cub_raycast.c \
			   cub_draw_rectangle.c \
			   cub_draw_3d_scene.c \
			   cub_math.c \
			   cub_mini_map.c \

HDR			 = cub3d.h

HDR			:= ${addprefix ${HDR_DIR}, ${HDR}}

OBJ			 = ${addprefix ${OBJ_DIR}, ${SRC:%.c=%.o}}

LIBFT		 = ${LFT_DIR}libft.a

VPATH		 = init/ exit/ run/

VPATH		:= ${SRC_DIR} ${addprefix ${SRC_DIR}, ${VPATH}}

INCLUDE		 = ${HDR_DIR} ${LFT_DIR}

INCLUDE		:= ${addprefix -I, ${INCLUDE}}

CFLAGS		 = -Wall -Werror -Wextra -g

MKFLAGS		 = -j35 -s --no-print-directory --directory=${LFT_DIR}

MLXFLAGS	 = -L./minilibx-linux -lmlx -lXext -lX11

MTFLAGS		 = -lm

OT_FLAGS	 = ${MLXFLAGS} ${MTFLAGS}

CC			 = cc

RM			 = rm -rf

UPDATE		 = NO

CUB3D_MSG	 = "\033[1;35mcub3D\033[0m:"

RECIPE_NAME	 = ${NAME}

all: set_recipe_name ${NAME}

${NAME}: ${OBJ_DIR} ${OBJ} FORCE
	@make ${MKFLAGS} | \
	tee /dev/stderr | \
	if grep -q "Nothing to be done for "; \
	then \
		if [ ${UPDATE} = YES ]; \
		then \
			echo ${CUB3D_MSG} Building ${NAME}; \
			${CC} ${CFLAGS} ${OBJ} ${INCLUDE} ${LIBFT} ${OT_FLAGS} -o ${NAME}; \
		else \
			echo ${CUB3D_MSG} Nothing to be done for \'${RECIPE_NAME}\'.; \
		fi \
	else \
		${CC} ${CFLAGS} ${OBJ} ${INCLUDE} ${LIBFT} ${OT_FLAGS} -o ${NAME}; \
	fi

clean:
	@echo ${CUB3D_MSG} Removing ${NAME}\'s objects
	@${RM} ${OBJ_DIR}
	@make clean ${MKFLAGS}

fclean:
	@echo ${CUB3D_MSG} Removing ${NAME}\'s  objects and binaries
	@make fclean ${MKFLAGS}
	@${RM} ${NAME} ${OBJ_DIR}

re: fclean all

${OBJ_DIR}:
	@mkdir -p ${OBJ_DIR}

${OBJ_DIR}%.o: %.c ${HDR}
	@echo ${CUB3D_MSG} Compiling $@
	@${CC} -c ${CFLAGS} ${INCLUDE} $< -o $@
	$(eval UPDATE = YES)

set_recipe_name:
	$(eval RECIPE_NAME = all)

FORCE:

.PHONY: all set_recipe_name clean fclean re FORCE

