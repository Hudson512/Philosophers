# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/23 08:16:52 by hmateque          #+#    #+#              #
#    Updated: 2024/10/08 11:13:57 by hmateque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
#FLAGS = -g -O0 -Wall -Wextra -Werror
RM = rm -f

SRC =   $(NAME).c\
        aux_functions.c\
        aux_2_functions.c\
		checker_error.c\
		error.c\
		mini_libft.c\
		free_functions.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
