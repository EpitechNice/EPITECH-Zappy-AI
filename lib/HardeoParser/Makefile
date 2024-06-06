##
## EPITECH PROJECT, 2024
## zappy
## File description:
## Makefile
##

CXX	=	g++

RM	=	rm -f

SRC	=	./JsonError.cpp		\
		./JsonObject.cpp	\
		./JsonString.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	libHardeoParser.a

CXXFLAGS	=	-Wall	\
			 	-Wextra

all:	$(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)
	cp $(NAME) ../

clean:
	$(RM) $(OBJ)
	$(RM) $(NAME)

fclean:	clean
	$(RM) ../$(NAME)
