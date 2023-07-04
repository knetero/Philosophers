# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/25 16:49:45 by abazerou          #+#    #+#              #
#    Updated: 2023/07/03 21:07:27 by abazerou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc -g
CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread

SRC = philo.c utils.c param_init.c time.c routine.c
OBJ = $(SRC:.c=.o)
NAME = philo

HEADER = philo.h


red    =   `tput setaf 1`
green  =   `tput setaf 2`
yellow =   `tput setaf 3`

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(green)✓ [Philo] IS READY "

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "$(red)✗ [OBJ]$(red)$(red) REMOVED"

fclean: clean
	@rm -f $(NAME)
	@echo "$(red)✗ [OBJ][EX]$(red)$(red) REMOVED"

re: fclean all
