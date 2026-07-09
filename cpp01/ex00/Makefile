# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/09 19:16:08 by lbueno-m          #+#    #+#              #
#    Updated: 2026/07/09 19:16:10 by lbueno-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      = c++
CFLAGS  = -Wall -Wextra -Werror -std=c++98
NAME    = zombie

ifeq ($(DEBUG),1)
CFLAGS += -g -O0
endif

SRC     =  main.cpp
SRC     += Zombie.cpp
SRC     += newZombie.cpp
SRC     += randomChump.cpp

OBJ     =  $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(NAME) compiled"

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
