# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/16 17:05:33 by lbueno-m          #+#    #+#              #
#    Updated: 2026/08/16 18:29:30 by lbueno-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      = c++
CFLAGS  = -Wall -Wextra -Werror -std=c++98
NAME    = sedpp

ifeq ($(DEBUG),1)
CFLAGS += -g -O0
endif

SRC     =   main.cpp
SRC     +=   Replacer.cpp

OBJ     =  $(SRC:.cpp=.o)

TEST_SRC = tests.cpp
TEST_SRC += Replacer.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(NAME) compiled"

tests: $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) -o tests
	@echo "tests compiled"
	./tests
	rm -f t1 t2 t3 t4 t5
	rm -f t1.replace t2.replace t3.replace t4.replace t5.replace

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TEST_OBJ)


fclean: clean
	rm -f $(NAME) tests

re: fclean all

.PHONY: all clean fclean re tests
