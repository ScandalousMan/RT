# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguemy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/21 15:23:17 by aguemy            #+#    #+#              #
#    Updated: 2017/03/31 14:44:44 by aguemy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3

SRC = ft_isascii.c ft_lstiter.c ft_memcpy.c ft_putendl_fd.c ft_strclr.c  \
	  ft_striteri.c ft_strncmp.c ft_strstr.c ft_isdigit.c ft_lstmap.c \
	  ft_memdel.c ft_putnbr.c ft_strcmp.c ft_strjoin.c ft_strncpy.c \
	  ft_strsub.c ft_isprint.c ft_lstnew.c ft_memmove.c ft_putnbr_fd.c \
	  ft_strcpy.c ft_strlcat.c ft_strnequ.c ft_strtrim.c ft_atoi.c ft_itoa.c \
	  ft_memalloc.c ft_memset.c ft_putstr.c ft_strdel.c ft_strlen.c \
	  ft_strnew.c ft_tolower.c ft_bzero.c ft_lstadd.c ft_memccpy.c \
	  ft_putchar.c ft_putstr_fd.c ft_strdup.c ft_strmap.c ft_strnstr.c \
	  ft_toupper.c ft_isalnum.c ft_lstdel.c ft_memchr.c ft_putchar_fd.c \
	  ft_strcat.c ft_strequ.c ft_strmapi.c ft_strrchr.c ft_isalpha.c \
	  ft_lstdelone.c ft_memcmp.c ft_putendl.c ft_strchr.c ft_striter.c \
	  ft_strncat.c ft_strsplit.c get_next_line.c ft_max.c ft_min.c ft_putdbl.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -c -I. $(SRC)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o: %.c libft.h
	@$(CC) $(CFLAGS) $(HEADER) -c -o $@ $<

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean
	make

.PHONY: all clean fclean re
