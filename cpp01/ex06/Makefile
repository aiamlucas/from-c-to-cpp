# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/17 10:50:46 by lbueno-m          #+#    #+#              #
#    Updated: 2026/08/17 10:56:16 by lbueno-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      = c++
CFLAGS  = -Wall -Wextra -Werror -std=c++98
NAME    = harlFilter

ifeq ($(DEBUG),1)
CFLAGS += -g -O0
endif

SRC     =  main.cpp
SRC     +=  Harl.cpp

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
