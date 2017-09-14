# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vacrozet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/14 19:43:12 by vacrozet          #+#    #+#              #
#    Updated: 2016/12/18 22:39:38 by jbouille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libmlx.a
SRCS= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c

OBJ1=$(SRCS:.c=.o)
OBJ=$(OBJ1:.m=.o)
CFLAGS+=-O2

# COLORS
C_NO = "\033[00m"
C_OK = "\033[34m"
C_GOOD = "\033[32m"
C_ERROR = "\033[31m"
C_WARN = "\033[33m"

# DEBUG MESSAGE
SUCCESS = [ $(C_GOOD)OK$(C_NO) ]
OK = [ $(C_OK)OK$(C_NO) ]

all: directories $(NAME)

$(NAME): $(OBJ)
			@echo $(SUCCESS)" Compiling" $(NAME) "\t\t"
			@ar -rc $(NAME) $(OBJ)
			@ranlib $(NAME)

%.o:%.c
			@clang $(CFLAGS) -o $@ -c $^ 2> /dev/null
%.o:%.m
			@clang $(CFLAGS) -o $@ -c $^ 2> /dev/null

clean:
		@echo $(OK)" Cleaning $(NAME) \t\t"
		@rm -f $(OBJ) *~

fclean: clean
		@echo $(OK)" Delete $(NAME) \t\t"
		@rm -f $(NAME) $(OBJ) *~

re: fclean all

.PHONY: all clean fclean re run directories cleanlib
