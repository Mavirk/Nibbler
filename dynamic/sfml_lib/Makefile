NAME		=	sfml.so
SRC			=	$(shell ls | grep ".cpp")
OBJ			=	$(subst .cpp,.o,$(SRC))

CPP			=	g++ -std=c++11
CPPFLAGS	=	-Wall -Wextra -Werror 
LDFLAGS		=	-dynamiclib -flat_namespace

all: $(NAME)

$(NAME):
	$(CPP) $(CPPFLAGS) $(LDFLAGS) $(SRC) ../IGraphics.cpp -o $(NAME) 

re: fclean all

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)