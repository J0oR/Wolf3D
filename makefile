# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: gruocco <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/23 13:00:25 by gruocco      #+#   ##    ##    #+#        #
#    Updated: 2018/10/23 13:00:28 by gruocco     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = wolf3d

CFLAGS = -Wall -Wextra -Werror -pthread

LIBS = libft/libft.a minilibx_macos/libmlx.a
LFLAGS = -framework OpenGL -framework AppKit -lpthread

INC= -I ft_include.h

SRC_NAME = main.c \
		ft_checks.c \
		ft_keys.c \
		ft_raycaster.c \
		ft_texture.c \
		ft_tools.c \
		ft_floor_ceiling.c

OBJ_NAME= $(SRC_NAME:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_NAME)
	@make -C libft/
	@make -C minilibx_macos/
	@gcc $(LIBS) $(LFLAGS)  $^ -o $@

%.o: %.c
	@gcc  $(CFLAGS) $(INC) -c $<

clean:
	@make clean -C libft/
	@make clean -C minilibx_macos/
	@/bin/rm -f $(OBJ_NAME)

fclean: clean
	@make fclean -C libft/
	@/bin/rm -f $(NAME)


re: fclean all
