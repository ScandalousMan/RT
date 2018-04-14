# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alex <alex@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/08/21 18:23:32 by malexand          #+#    #+#              #
#    Updated: 2017/11/20 00:23:47 by alex             ###   ########.fr        #
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

LIBJSON_PATH = ./libjson
LIBJSON_FILE = $(LIBJSON_PATH)/libjson.a
LIBJSON_DEP = $(LIBJSON_PATH)/sources/*

# Link lib : "-L FOLDER -lXXX" where XXX = libXXX.a

ifeq ($(OS), Linux)
	LFLAGS = -L./libjson -ljson -L./libft -lft `pkg-config --libs glew` `pkg-config --libs sdl2` -lSDL2_image -lGL -lm -lGLU
	INCLUDE = -I./incs -I./libft/incs -I./libjson
else
	LFLAGS = -L./libft -lft -L./libjson -ljson `pkg-config --libs glew` `pkg-config --libs sdl2` -lSDL2_image -framework OpenGL -lm
	INCLUDE = -I./incs -I./libft/incs -I./libjson
endif

OUT_DIR = objs
SRC_DIR = srcs
INC_DIR = incs

SDIR =		./srcs/
SRCS =		closest.c components.c cone.c cone_tools.c constructor.c \
			cylindre.c cylindre_tools.c display.c distance.c ellipsoide.c \
			graph_init.c key_func.c light.c main.c \
			new_functions.c nukl_gui.c object_parser.c \
			plane.c postprocessing.c sdl_draw.c sdl_evts.c sdl_init.c \
			sdl_utils.c sphere.c threads.c vec_tools.c vec_tools2.c \
			vec_tools3.c file.c json_to_objects.c objects_storage.c rt_parser.c
SRCC =		$(addprefix $(SDIR),$(SRCS))

ODIR =		./objs/
OBJS =		$(SRCS:.c=.o)
OBCC =		$(addprefix $(ODIR),$(OBJS))

all: directories $(EXEC)

$(LIBFT_FILE): $(LIBFT_DEP)
ifeq ($(OS), Linux)
	@echo -e "\x1B[34mLibft:\x1B[0m"
	@make -C ./libft
else
	@echo "\x1B[34mLibft:\x1B[0m"
	@make -C ./libft
endif

$(LIBJSON_FILE): $(LIBJSON_DEP)
ifeq ($(OS), Linux)
	@echo -e "\x1B[34mLibjson:\x1B[0m"
	@make -C ./libjson
else
	@echo "\x1B[34mLibjson:\x1B[0m"
	@make -C ./libjson
endif

$(EXEC): $(OBCC) $(LIBFT_FILE) $(LIBJSON_FILE)
ifeq ($(OS), Linux)
	@echo -e "\x1B[34m$(EXEC):\x1B[0m"
	$(CC) $(CFLAGS) -o $@ $(OBCC) $(INCLUDE) $(LFLAGS)
	@echo -e "\x1b[36m  + Compile program:\x1B[0m $@"
else
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
	@make -C ./libjson clean
	@rm -rf $(OUT_DIR)
ifeq ($(OS), Linux)
	@echo -e "\x1B[31m  - Remove:\x1B[0m RT objs"
else
	@echo "\x1B[31m  - Remove:\x1B[0m RT objs"
endif

fclean: clean
	@pkill -9 RT | true
	@make -C ./libft fclean
	@make -C ./libjson fclean
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

depend:
	@makedepend -- -Y -O -DHACK $(INCLUDE) -- $(SRCC) >& /dev/null

norm:
	@echo "\x1B[31m\c"
	@norminette srcs/* incs/* | grep -B 1 "Error" || true
	@echo "\x1B[0m\c"


.PHONY: all clean fclean re run directories cleanlib norm
# DO NOT DELETE

./srcs/closest.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/closest.o: ./incs/nuklear_sdl_gl3.h
./srcs/components.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/components.o: ./incs/nuklear_sdl_gl3.h
./srcs/cone.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/cone.o: ./incs/nuklear_sdl_gl3.h
./srcs/cone_tools.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/cone_tools.o: ./incs/nuklear_sdl_gl3.h
./srcs/constructor.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/constructor.o: ./incs/nuklear_sdl_gl3.h
./srcs/cylindre.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/cylindre.o: ./incs/nuklear_sdl_gl3.h
./srcs/cylindre_tools.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/cylindre_tools.o: ./incs/nuklear_sdl_gl3.h
./srcs/display.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/display.o: ./incs/nuklear_sdl_gl3.h
./srcs/distance.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/distance.o: ./incs/nuklear_sdl_gl3.h
./srcs/ellipsoide.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/ellipsoide.o: ./incs/nuklear_sdl_gl3.h
./srcs/graph_init.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/graph_init.o: ./incs/nuklear_sdl_gl3.h
./srcs/key_func.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/key_func.o: ./incs/nuklear_sdl_gl3.h
./srcs/light.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/light.o: ./incs/nuklear_sdl_gl3.h
./srcs/main.o: ./incs/implementation.h ./incs/rt.h ./libft/incs/libft.h
./srcs/main.o: ./incs/nuklear.h ./incs/nuklear_sdl_gl3.h ./incs/rt_parser.h
./srcs/new_functions.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/new_functions.o: ./incs/nuklear_sdl_gl3.h
./srcs/nukl_gui.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/nukl_gui.o: ./incs/nuklear_sdl_gl3.h
./srcs/object_parser.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/object_parser.o: ./incs/nuklear_sdl_gl3.h
./srcs/plane.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/plane.o: ./incs/nuklear_sdl_gl3.h
./srcs/postprocessing.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/postprocessing.o: ./incs/nuklear_sdl_gl3.h
./srcs/sdl_draw.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/sdl_draw.o: ./incs/nuklear_sdl_gl3.h
./srcs/sdl_evts.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/sdl_evts.o: ./incs/nuklear_sdl_gl3.h
./srcs/sdl_init.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/sdl_init.o: ./incs/nuklear_sdl_gl3.h
./srcs/sdl_utils.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/sdl_utils.o: ./incs/nuklear_sdl_gl3.h
./srcs/sphere.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/sphere.o: ./incs/nuklear_sdl_gl3.h
./srcs/threads.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/threads.o: ./incs/nuklear_sdl_gl3.h
./srcs/vec_tools.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/vec_tools.o: ./incs/nuklear_sdl_gl3.h
./srcs/vec_tools2.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/vec_tools2.o: ./incs/nuklear_sdl_gl3.h
./srcs/vec_tools3.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/vec_tools3.o: ./incs/nuklear_sdl_gl3.h
./srcs/file.o: ./libft/incs/libft.h ./libjson/json.h ./libjson/json_parse.h
./srcs/json_to_objects.o: ./libjson/json.h ./incs/rt_objects.h ./incs/rt.h
./srcs/json_to_objects.o: ./libft/incs/libft.h ./incs/nuklear.h
./srcs/json_to_objects.o: ./incs/nuklear_sdl_gl3.h ./incs/objects_storage.h
./srcs/objects_storage.o: ./incs/objects_storage.h ./libjson/json.h
./srcs/objects_storage.o: ./incs/rt.h ./libft/incs/libft.h ./incs/nuklear.h
./srcs/objects_storage.o: ./incs/nuklear_sdl_gl3.h ./incs/rt_objects.h
./srcs/rt_parser.o: ./libjson/json_parse.h ./libjson/json.h
./srcs/rt_parser.o: ./libjson/json_free.h ./incs/rt.h ./libft/incs/libft.h
./srcs/rt_parser.o: ./incs/nuklear.h ./incs/nuklear_sdl_gl3.h ./incs/file.h
./srcs/rt_parser.o: ./incs/rt_objects.h
