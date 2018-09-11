NAME		=	ncur.so
SRC			=	ncurses.cpp \
				../Snake.cpp

OBJ			=	$(patsubst %.cpp, %.o, $(SRC))

CPP			=	clang++ -std=c++11 -stdlib=libc++
CPPFLAGS	=	-Wall -Wextra -Werror 
LDFLAGS		=	-dynamiclib -flat_namespace
LIB			=	-lncurses

all: $(NAME)

$(NAME):
	$(CPP) $(CPPFLAGS) $(LDFLAGS) $(SRC) $(LIB) -o $(NAME) 

re: fclean all

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)