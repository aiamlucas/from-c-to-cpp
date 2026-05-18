# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/09 15:26:18 by lbueno-m          #+#    #+#              #
#    Updated: 2026/05/18 18:01:07 by lbueno-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      = c++
CFLAGS  = -Wall -Wextra -Werror -std=c++98
NAME    = phonebook

ifeq ($(DEBUG),1)
CFLAGS += -g -O0
endif

SRC     =  main.cpp
SRC     += Contact.cpp
SRC     += PhoneBook.cpp
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
