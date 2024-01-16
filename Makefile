# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcot <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/12 15:00:07 by gcot              #+#    #+#              #
#    Updated: 2023/06/16 12:52:52 by gcot             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = game_of_life

CC = gcc

SRC = main.c controls.c set_game.c

FLAGS = -Wall -Werror -Wextra

all :
	gcc $(FLAGS) $(SRC) minilibx/libmlx_Linux.a -lX11 -lXext -o $(NAME)

clean :
	rm -rf *.o

fclean : clean
	rm -rf $(NAME)

re : fclean all
