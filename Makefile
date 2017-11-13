# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alex <alex@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/08/21 18:23:32 by malexand          #+#    #+#              #
#    Updated: 2017/11/13 17:56:55 by jbouille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC = RT

DEBUG = no
CC = clang
OS := $(shell uname -s)
MAKEFLAGS += --silent

export

ifeq ($(DEBUG), yes)
	CFLAGS = -std=c99 -pedantic -g -ggdb `pkg-config --cflags sdl2` `pkg-config --cflags glew`
else
	CFLAGS =  -Wall -Werror -Wextra -O3 -Ofast `pkg-config --cflags sdl2` `pkg-config --cflags glew`
endif

LIBFT_PATH = ./libft
LIBFT_FILE = $(LIBFT_PATH)/libft.a
LIBFT_DEP = $(LIBFT_PATH)/srcs/*

# Link lib : "-L FOLDER -lXXX" where XXX = libXXX.a

ifeq ($(OS), Linux)
	LFLAGS = -L./libft -lft `pkg-config --libs glew` `pkg-config --libs sdl2` -lGL -lm -lGLU
	INCLUDE = -I./incs -I/usr/include/mlx
else
	LFLAGS = -L./libft -lft `pkg-config --libs glew` `pkg-config --libs sdl2` -framework OpenGL -lm -Llibjson -ljson
	INCLUDE = -I./incs -I./libft -I./libjson
endif

OUT_DIR = objs
SRC_DIR = srcs
INC_DIR = incs

SDIR =		./srcs/
#SRCS =		$(notdir $(shell ls $(SRC_DIR)/*.c))
SRCS =		closest.c components.c cone.c cone_tools.c constructor.c \
			cylindre.c cylindre_tools.c display.c distance.c ellipsoide.c \
			ft_atod.c graph_init.c key_func.c light.c main.c \
			new_functions.c nukl_gui.c object_parser.c \
			plane.c postprocessing.c sdl_draw.c sdl_evts.c sdl_init.c \
			sdl_utils.c sphere.c threads.c vec_tools.c vec_tools2.c \
			vec_tools3.c \
			file.c json_to_objects.c objects_storage.c rt_parser.c
SRCC =		$(addprefix $(SDIR),$(SRCS))

ODIR =		./objs/
OBJS =		$(SRCS:.c=.o)
OBCC =		$(addprefix $(ODIR),$(OBJS))

all: directories $(EXEC)

$(LIBFT_FILE): $(LIBFT_DEP)
ifeq ($(OS), Linux)
	@echo -e "\x1B[34mLibft:\x1B[0m\n"
	@make -C ./libft
else
	@echo "\x1B[34mLibft:\x1B[0m\n"
	@make -C ./libft
endif

$(EXEC): $(OBCC) $(LIBFT_FILE)
ifeq ($(OS), Linux)
	@echo -e "\x1B[34m$(EXEC):\x1B[0m"
	$(CC) $(CFLAGS) -o $@ $(OBCC) $(INCLUDE) $(LFLAGS)
	@echo -e "\x1b[36m  + Compile program:\x1B[0m $@"
else
	@make -C libjson
	@echo "\x1B[34m$(EXEC):\x1B[0m"
	@$(CC) $(CFLAGS) -o $@ $(OBCC) $(INCLUDE) $(LFLAGS)
	@echo "\x1b[36m  + Compile program:\x1B[0m $@"
	@echo "\x1B[31m\c"
	# @norminette srcs/* incs/* | grep -B 1 "Error" || true
	@echo "\x1B[0m\c"
endif

$(ODIR)%.o: $(SDIR)%.c
	$(CC) $^ $(CFLAGS) -c -o $@ $(INCLUDE)
ifeq ($(OS), Linux)
	@echo -e "\r\x1B[32m  + Compile:\x1B[0m $(notdir $^)"
else
	@echo "\r\x1B[32m  + Compile:\x1B[0m $(notdir $^)"
endif

directories: ${OUT_DIR} ${SRC_DIR} ${INC_DIR}

${OUT_DIR}:
	@mkdir -p ${OUT_DIR}

${SRC_DIR}:
	@mkdir -p ${SRC_DIR}

${INC_DIR}:
	@mkdir -p ${INC_DIR}

clean:
	@make -C ./libft clean
	@make -C libjson clean
	@rm -rf $(OUT_DIR)
ifeq ($(OS), Linux)
	@echo -e "\x1B[31m  - Remove:\x1B[0m objs"
else
	@echo "\x1B[31m  - Remove:\x1B[0m objs"
endif

fclean: clean
	@make -C ./libft delete
	@make -C libjson fclean
	@rm -f $(EXEC)
ifeq ($(OS), Linux)
	@echo -e "\x1B[31m  - Remove:\x1B[0m $(EXEC)"
else
	@echo "\x1B[31m  - Remove:\x1B[0m $(EXEC)"
endif

re: fclean
	make

run: re
	@./$(EXEC)

cleanlib:
	@make -C ./libft fclean

norm:
	@echo "\x1B[31m\c"
	@norminette srcs/* incs/* | grep -B 1 "Error" || true
	@echo "\x1B[0m\c"


.PHONY: all clean fclean re run directories cleanlib norm
