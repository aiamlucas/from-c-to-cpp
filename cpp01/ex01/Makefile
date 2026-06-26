CC      = c++
CFLAGS  = -Wall -Wextra -Werror -std=c++98
NAME    = zombie

ifeq ($(DEBUG),1)
CFLAGS += -g -O0
endif

SRC     =  main.cpp
SRC     += Zombie.cpp
SRC     += zombieHorde.cpp

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
