# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joe <joe@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/05 17:11:44 by joe               #+#    #+#              #
#    Updated: 2024/03/05 17:11:44 by joe              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# *==============================================================================
# *VARIABLES
# *==============================================================================

NAME		= cub3D
CC			= cc
LINKS	 	= -lmlx -lXext -lX11 -Llibft -Lminilibx_linux 
CFLAGS		= -Wall -Werror -Wextra
HEADERS		:=	includes
LIBFT	 	= ./libft/libft.a 
SRCS		= ./sources/main.c 
OBJS		:=	$(SRCS:.c=.o)


VGFLAGS		:=	--leak-check=full --show-leak-kinds=all

# *==============================================================================
# *COLORS
# *==============================================================================

GREEN		:=	\033[1;32m
RED			:=	\033[1;31m
WHT			:=	\033[1;37m
EOC			:=	\033[1;0m

# ==============================================================================
# RECIPES	
# ==============================================================================

all:		$(NAME)

%.o:		%.c
			@$(CC) $(CFLAGS) -I $(HEADERS) -c $< -o $@

$(NAME):	$(OBJS) $(LIBFT)
			@echo "$(WHT)Compiling CUB3D...$(EOC)"
			@$(CC) $(OBJS) $(LINKS) $(LIBFT) -o $@
			@echo "$(GREEN)CUB3D build completed.$(EOC)"

$(LIBFT):
			@echo "$(WHT)Compiling libft...$(EOC)"
			@make -C libft
			@echo "$(GREEN)Libft done.$(EOC)"

clean:
			@echo "$(WHT)Removing .o files...$(EOC)"
			@rm -f $(OBJS)
			@make -C libft clean
			@echo "$(GREEN)Clean done.$(EOC)"

fclean:		clean
			@echo "$(WHT)Removing object- and binary -files...$(EOC)"
			@rm -f $(NAME)
			@make -C libft fclean
			@echo "$(GREEN)Fclean done.$(EOC)"

re:			fclean all

run:		all
			clear
			./$(NAME) $(ARGV)

vg:			all
			clear
			valgrind $(VGFLAGS) ./$(NAME) $(ARGV)

.PHONY:		all clean fclean re vg
