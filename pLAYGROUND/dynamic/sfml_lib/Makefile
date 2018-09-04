NAME		=	sfml.so
SRC			=	$(shell ls | grep ".cpp")
OBJ			=	$(subst .cpp,.o,$(SRC))

CPP			=	g++ -std=c++11
CPPFLAGS	=	-Wall -Wextra -Werror 
LDFLAGS		=	-dynamiclib -flat_namespace
INCLUDE		= 	-I ~/.brew/include/SDL2
LIB			=	-L ~/.brew/lib -lSDL2

all: $(NAME)

$(NAME):
	$(CPP) $(CPPFLAGS) $(LDFLAGS) $(SRC) ../IGraphics.cpp $(INCLUDE) $(LIB) -o $(NAME) 

re: fclean all

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)