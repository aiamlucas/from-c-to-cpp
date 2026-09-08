# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/08 08:36:07 by lbueno-m          #+#    #+#              #
#    Updated: 2026/09/08 10:08:55 by lbueno-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      = c++
CPPFLAGS  = -Wall -Wextra -Werror -std=c++98
NAME    = animal

ifeq ($(DEBUG),1)
CPPFLAGS += -g -O0
endif

SRC     =  main.cpp
SRC     += Animal.cpp
SRC     += Cat.cpp
SRC     += Dog.cpp
SRC     += WrongAnimal.cpp
SRC     += WrongCat.cpp
SRC     += Brain.cpp

OBJ     =  $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CPPFLAGS) $(OBJ) -o $(NAME)
	@echo "$(NAME) compiled"

%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
