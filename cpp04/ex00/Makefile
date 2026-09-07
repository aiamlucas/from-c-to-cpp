# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/07 17:59:40 by lbueno-m          #+#    #+#              #
#    Updated: 2026/09/07 19:16:52 by lbueno-m         ###   ########.fr        #
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
