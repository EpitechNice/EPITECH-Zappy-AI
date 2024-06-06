##
## EPITECH PROJECT, 2024
## zappy
## File description:
## Makefile
##

SRC	=	src/Main.cpp	\
		src/Parser/Parser.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	zappy_ai

CXXFLAGS	=	-Wall					\
	 			-Wextra 				\
				-std=c++20				\
				-I./include				\
				-I./src/				\
				-I./lib/HardeoParser	\
				-Llib					\
				-lHardeoParser

CC	=	g++

ANGLE = "\u2514\u2500"

GREEN = "\033[1;32m"
YELLOW = "\033[1;33m"
BLUE = "\033[1;34m"
MAGENTA = "\033[1;35m"
RESET = "\033[0m"

all:	start	$(NAME)

start:
	@echo -ne $(MAGENTA)
	@echo -e "Lib compilation..." $(RESET)
	@make -sC lib/HardeoParser
	@echo -ne $(GREEN)
	@echo -e "Lib compiled" $(RESET)
	@echo -ne $(GREEN)
	@echo -e "Starting compilation of" $(MAGENTA) $(NAME) $(RESET)
	@echo -ne $(BLUE)
	@echo -e "Compiling SRC..." $(RESET)

$(NAME):	$(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(CXXFLAGS)
	@echo -ne $(GREEN)
	@echo -e "Compiled" $(MAGENTA) $(NAME) $(RESET)

clean:
	@echo -ne $(YELLOW)
	@echo -e "Cleaning repository..." $(RESET)
	@make -sC lib/HardeoParser clean
	@rm -f $(OBJ)
	@rm -f *~

fclean:	clean
	@rm -f $(NAME)
	@make -sC lib/HardeoParser fclean

re:	fclean all

%.o:	%.cpp
	@echo -ne $(BLUE)
	@echo -e "  " $(ANGLE) $(RESET) $<
	@$(CC) -c -o $@ $< $(CXXFLAGS)

debug:	CXXFLAGS += -g3
debug:	re

run:	all
	./$(NAME)

valgrind:	debug
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

.PHONY:	all clean fclean re
