# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alex <alex@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/14 15:27:27 by malexand          #+#    #+#              #
#    Updated: 2017/11/15 17:25:11 by alex             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = libjson.a
OS := $(shell uname -s)

ifndef CC
CC 					= clang
endif
ifndef DEBUG
DEBUG 				= no
endif

ifeq ($(OS), Linux)
	INCLUDES = -I. -I./includes -I../libft/incs
else
	INCLUDES = -I. -I./includes -I../libft/incs
endif

ifeq ($(DEBUG), yes)
	CFLAGS = -std=c99 -pedantic -g -ggdb -Wall -Wextra -Werror
else
	CFLAGS =  -Wall -Werror -Wextra -O3 -Ofast
endif

SRC = json_parse.c json_type.c parse_key_value.c parse_number.c parse_string.c stringify.c free.c
DIR_SRC = sources/
DIR_OBJ = objects/
OBJ = $(addprefix $(DIR_OBJ),$($(sort SRC):.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@printf "%-60s" "-----> Compiling...     ~>  $@"
ifeq ($(OS), Linux)
	@ar rc $(NAME) $(OBJ) 2> /dev/null && echo -e "\033[32m [OK] \033[0m" || echo -e "\033[31m[FAIL]\033[0m"
else
	@ar rc $(NAME) $(OBJ) 2> /dev/null && echo "\033[32m [OK] \033[0m" || echo "\033[31m[FAIL]\033[0m"
endif
	@ranlib $(NAME)

$(DIR_OBJ)%.o: $(DIR_SRC)%.c
	@mkdir -p $(DIR_OBJ)
	@mkdir -p $(DIR_OBJ)ft_printf/
	@printf "%-60s" "-----> Compiling...     ~>  $@"
ifeq ($(OS), Linux)
	@gcc $(CFLAGS) $(INCLUDES) -o $@ -c $< && echo -e "\033[32m [OK] \033[0m" || echo -e "\033[31m[FAIL]\033[0m"
else
	@gcc $(CFLAGS) $(INCLUDES) -o $@ -c $< && echo "\033[32m [OK] \033[0m" || echo "\033[31m[FAIL]\033[0m"
endif

clean:
	@rm -rf $(DIR_OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all