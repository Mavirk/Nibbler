NAME		=	alg.so
SRC			=	$(shell ls | grep ".cpp")
OBJ			=	$(subst .cpp,.o,$(SRC))

CPP			=	g++ -std=c++11
CPPFLAGS	=	-Wall -Wextra -Werror 
LDFLAGS		=	-dynamiclib -flat_namespace
INCLUDE		= 	-I ~/.brew/include
LIB			=	 -L ~/.brew/lib -lallegro_color -lallegro_ttf -lallegro_font -lallegro_image -lallegro_physfs -lallegro_primitives -lallegro_dialog -lallegro
LIBALG2 = $(shell pkg-config --cflags --libs allegro-5 allegro_main-5 allegro_color-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_physfs-5 allegro_primitives-5 allegro_dialog-5)

all: $(NAME)

$(NAME):
	$(CPP) $(CPPFLAGS) $(LDFLAGS) $(SRC) ../Snake.cpp ../IGraphics.cpp $(INCLUDE) $(LIB) -o $(NAME) 
	# $(CPP) $(CPPFLAGS) $(LDFLAGS) $(SRC) ../Snake.cpp ../IGraphics.cpp $(LIBALG2) -o $(NAME)

re: fclean all

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)