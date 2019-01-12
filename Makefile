# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malexand <malexand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/08/21 18:23:32 by malexand          #+#    #+#              #
#    Updated: 2019/01/12 15:14:53 by malexand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC = RT

CC ?= clang
DEBUG ?= false

OS := $(shell uname -s)
DEPEND_FRAGMENT = Make.depend
MAKEFLAGS += --silent

export

ifeq ($(DEBUG), true)
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
	INCLUDE = -I./incs -I./libft/incs -I./libjson -I./nuklear
else
	LFLAGS = -L./libft -lft -L./libjson -ljson `pkg-config --libs glew` `pkg-config --libs sdl2` -lSDL2_image -framework OpenGL -lm
	INCLUDE = -I./incs -I./libft/incs -I./libjson -I./nuklear
endif

OUT_DIR = objs
OUT_OBJECT_DIR = $(OUT_DIR)/objects
OUT_SDL_DIR = $(OUT_DIR)/sdl
OUT_NUKL_GUI_DIR = $(OUT_DIR)/nukl_gui
SRC_DIR = srcs
INC_DIR = incs

SDIR =		./srcs/

SRCS =		blur.c \
			colors.c \
			components.c \
			constructor_pixel.c \
			constructor_stereoscopy.c \
			constructor.c \
			display.c \
			distance.c \
			file.c \
			first_obj_hit.c \
			free.c \
			json_is_type.c \
			json_to_objects_2.c \
			json_to_objects.c \
			light.c \
			lights_storage.c \
			main.c \
			nukl_gui/camera.c \
			nukl_gui/global_settings.c \
			nukl_gui/gui.c \
			nukl_gui/objects_1.c \
			nukl_gui/objects_utils_1.c \
			nukl_gui/objects_utils.c \
			nukl_gui/objects.c \
			objects_color.c \
			objects_duplicate.c \
			objects_filler_1.c \
			objects_filler_2.c \
			objects_moves.c \
			objects_router.c \
			objects_storage_2.c \
			objects_storage_3.c \
			objects_storage.c \
			objects/cone_tools.c \
			objects/cone.c \
			objects/cube_tools.c \
			objects/cube.c \
			objects/cylindre_tools.c \
			objects/cylindre.c \
			objects/plane_tools.c \
			objects/plane.c \
			objects/quadric_tools.c \
			objects/quadric.c \
			objects/sphere_tools.c \
			objects/sphere.c \
			perlin.c \
			perturbations.c \
			postprocessing_2.c \
			postprocessing.c \
			ray_color.c \
			referential.c \
			refraction.c \
			rotations.c \
			rt_parser.c \
			rt_tracer.c \
			save_img.c \
			sdl/draw.c \
			sdl/events.c \
			sdl/init_window.c \
			sdl/init.c \
			sdl/keyboard.c \
			sdl/utils.c \
			threads_init.c \
			threads.c \
			vec_tools.c \
			vec_tools2.c \
			vec_tools3.c

SRCC =		$(addprefix $(SDIR),$(SRCS))

ODIR =		./objs/
OBJS =		$(SRCS:.c=.o)
OBCC =		$(addprefix $(ODIR),$(OBJS))

all: directories $(EXEC) $(DEPEND_FRAGMENT)

-include $(DEPEND_FRAGMENT)

$(LIBFT_FILE): $(LIBFT_DEP)
ifeq ($(OS), Linux)
	@echo -e "\x1B[34mLibft:\x1B[0m"
	@DEBUG=$(DEBUG) make -C ./libft
else
	@echo "\x1B[34mLibft:\x1B[0m"
	@DEBUG=$(DEBUG) make -C ./libft
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
	@norminette srcs/* incs/* | grep -B 1 "Error" || true
	@echo "\x1B[0m\c"
endif

$(ODIR)%.o: $(SDIR)%.c
	$(CC) $< $(CFLAGS) -c -o $@ $(INCLUDE)
ifeq ($(OS), Linux)
	@echo -e "\r\x1B[32m  + Compile:\x1B[0m $(notdir $<)"
else
	@echo "\r\x1B[32m  + Compile:\x1B[0m $(notdir $<)"
endif

$(DEPEND_FRAGMENT): $(SRCC)
	@touch $(DEPEND_FRAGMENT)
	@makedepend -f $(DEPEND_FRAGMENT) -- -Y -O -DHACK $(CFLAGS) $(CXXFLAGS) $(INCLUDE) -- $(SRCC) >& /dev/null
	@sed 's/.\/srcs/.\/objs/g' $(DEPEND_FRAGMENT) > $(DEPEND_FRAGMENT).bak
	@mv $(DEPEND_FRAGMENT).bak $(DEPEND_FRAGMENT)

directories: ${OUT_DIR} ${SRC_DIR} ${INC_DIR} ${OUT_OBJECT_DIR} ${OUT_SDL_DIR} ${OUT_NUKL_GUI_DIR}

${OUT_DIR}:
	@mkdir -p ${OUT_DIR}

${SRC_DIR}:
	@mkdir -p ${SRC_DIR}

${INC_DIR}:
	@mkdir -p ${INC_DIR}

${OUT_OBJECT_DIR}:
	@mkdir -p ${OUT_OBJECT_DIR}

${OUT_SDL_DIR}:
	@mkdir -p ${OUT_SDL_DIR}

${OUT_NUKL_GUI_DIR}:
	@mkdir -p ${OUT_NUKL_GUI_DIR}

clean:
	@make -C ./libft clean
	@make -C ./libjson clean
	@rm -rf $(OUT_DIR) $(DEPEND_FRAGMENT)
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

run: all
	@./$(EXEC)

norm:
	@echo "\x1B[31m\c"
	@norminette srcs/* incs/* | grep -B 1 "Error" || true
	@echo "\x1B[0m\c"

.PHONY: all clean fclean re run directories cleanlib norm
