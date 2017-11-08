.PHONY: all, clean, fclean, re
NAME = libjson.a
SRC = json_parse.c json_type.c parse_key_value.c parse_number.c parse_string.c stringify.c
DIR_SRC = sources/
DIR_OBJ = objects/
OBJ = $(addprefix $(DIR_OBJ),$($(sort SRC):.c=.o))
CFLAGS = -Wall -Wextra -Werror -O3 -Ofast
INCLUDES = -I. -Iincludes -I../libft

all: $(NAME)

$(NAME): $(OBJ)
	@printf "%-60s" "-----> Compiling...     ~>  $@"
	@ar rc $(NAME) $(OBJ) 2> /dev/null && echo "\033[32m [OK] \033[0m" || echo "\033[31m[FAIL]\033[0m"
	@ranlib $(NAME)

$(DIR_OBJ)%.o: $(DIR_SRC)%.c
	@mkdir -p $(DIR_OBJ)
	@mkdir -p $(DIR_OBJ)ft_printf/
	@printf "%-60s" "-----> Compiling...     ~>  $@"
	@gcc $(CFLAGS) $(INCLUDES) -o $@ -c $< && echo "\033[32m [OK] \033[0m" || echo "\033[31m[FAIL]\033[0m"
##	@gcc $(CFLAGS) -Iincludes -Iincludes/ft_printf -o $@ -c $<

clean:
	@rm -rf $(DIR_OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
