# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/23 08:16:52 by hmateque          #+#    #+#              #
#    Updated: 2024/10/09 11:27:01 by hmateque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc -fsanitize=thread
FLAGS = -g -O0 -Wall -Wextra -Werror
RM = rm -f

SRC =   $(NAME).c\
        aux_functions.c\
        aux_funt_monitor.c\
		aux_funt_filosofar_1.c\
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
