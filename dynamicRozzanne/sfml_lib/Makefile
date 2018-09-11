NAME		=	sfml.so
SRC			=	sfml.cpp \
				../Snake.cpp

OBJ			=	$(patsubst %.cpp, %.o, $(SRC))

CPP			=	clang++ -std=c++11 -stdlib=libc++
CPPFLAGS	=	-Wall -Wextra -Werror 
LDFLAGS		=	-dynamiclib -flat_namespace
INCLUDE		= 	-I ~/.brew/include
LIB			=	-L ~/.brew/lib -lsfml-system -lsfml-window -lsfml-graphics

all: $(NAME)

$(NAME):
	$(CPP) $(CPPFLAGS) $(LDFLAGS) $(SRC) $(INCLUDE) $(LIB) -o $(NAME) 

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all