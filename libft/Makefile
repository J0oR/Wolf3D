# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gruocco <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/08 12:25:16 by gruocco           #+#    #+#              #
#    Updated: 2017/11/08 12:25:18 by gruocco          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME= libft.a

CFLAGS= -Wall -Wextra -Werror

INC= -I libft.h get_next_line.h

SRC=  ft_bzero.c \
		 ft_memccpy.c \
         ft_memchr.c \
         ft_memcpy.c \
         ft_memmove.c \
         ft_memcmp.c \
         ft_strlen.c \
         ft_strdup.c \
         ft_strcpy.c \
         ft_strncpy.c \
         ft_strcat.c \
         ft_strncat.c \
         ft_strlcat.c \
         ft_strchr.c \
         ft_strrchr.c \
         ft_strstr.c \
         ft_strnstr.c \
         ft_strcmp.c \
         ft_strncmp.c \
         ft_atoi.c \
         ft_isalpha.c \
         ft_isdigit.c \
         ft_isalnum.c \
         ft_isascii.c \
         ft_isprint.c \
         ft_toupper.c \
         ft_tolower.c \
         ft_memalloc.c \
         ft_memdel.c \
         ft_strnew.c \
         ft_strdel.c \
         ft_strclr.c \
         ft_striter.c \
         ft_striteri.c \
         ft_strmap.c \
         ft_strmapi.c \
         ft_strsub.c \
         ft_strjoin.c \
         ft_strsplit.c \
         ft_memset.c \
         ft_strtrim.c \
         ft_strequ.c \
         ft_strnequ.c \
         ft_putchar.c \
         ft_putnbr.c \
         ft_putstr.c \
         ft_putendl.c \
         ft_putchar_fd.c \
         ft_putstr_fd.c \
         ft_putendl_fd.c \
         ft_putnbr_fd.c \
         ft_itoa.c \
         ft_lstnew.c \
         ft_lstdelone.c \
         ft_lstdel.c \
         ft_lstadd.c \
         ft_lstiter.c \
         ft_lstmap.c \
         ft_swap.c \
         get_next_line.c

OBJ= $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)

%.o: %.c
	@gcc  $(CFLAGS) $(INC) -c $<

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)


re: fclean all

