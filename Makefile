# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguemy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/27 15:52:45 by aguemy            #+#    #+#              #
#    Updated: 2017/06/04 22:35:54 by aguemy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
CC = gcc
CFLAGS =  -Wall -Werror -Wextra
HEADER = -I./include
OBJ = $(SRC:.c=.o)
LIB_PATH = ./libft/
MLX_PATH = ./lib-mlx/
LFLAGS = -L$(LIB_PATH) -lft -L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit
LIB = $(LIB_PATH)libft.a
SRC = main.c \
	parser.c \
	parser2.c \
	object_parser.c \
	components.c \
	constructor.c \
	vec_tools.c \
	distance.c \
	filler.c \
	closest.c \
	cone.c \
	cylindre.c \
	key_func.c \
	ft_atod.c \
	display.c \
	new_functions.c

# COLORS
C_NO = "\033[00m"
C_OK = "\033[34m"
C_GOOD = "\033[32m"
C_ERROR = "\033[31m"
C_WARN = "\033[33m"

# DEBUG MESSAGE
SUCCESS = [ $(C_GOOD)OK$(C_NO) ]
OK = [ $(C_OK)OK$(C_NO) ]

all: lib-mlx/libmlx.a libft/libft.a $(NAME)

libft/libft.a:
	@make -C $(LIB_PATH)

lib-mlx/libmlx.a:
	@make -C $(MLX_PATH)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(LFLAGS) $(HEADER)
	@echo $(SUCCESS)" Compiling" $(NAME) "\t\t"

%.o: %.c ./include/rt.h
	@$(CC) $(CFLAGS) $(HEADER) -c -o $@ $<
	@echo $(OK)" Linking $< \t\t"

clean:
	@rm -f $(OBJ)
	@make -C $(LIB_PATH) clean
	@make -C $(MLX_PATH) clean
	@echo $(OK)" Cleaning $(NAME) \t\t"

fclean: clean
	@rm -f $(NAME)
	@make -C $(MLX_PATH) fclean
	@make -C $(LIB_PATH) fclean
	@echo $(OK)" Delete $(NAME) \t\t"

re: fclean
	make

.PHONY: all clean fclean re $(LIB)
