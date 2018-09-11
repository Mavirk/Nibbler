NAME		=	alg.so
SRC			=	Allegro.cpp \
				../Snake.cpp

OBJ			=	$(patsubst %.cpp, %.o, $(SRC))

CPP			=	clang++ -std=c++11 -stdlib=libc++
CPPFLAGS	=	-fPIC -Wall -Wextra -Werror 
LDFLAGS		=	-dynamiclib -flat_namespace
INCLUDE		= 	-I ~/.brew/include
LIB			=	 -L ~/.brew/lib -lallegro -lallegro_color -lallegro_ttf -lallegro_font -lallegro_physfs -lallegro_primitives
#LIBALG2 = $(shell pkg-config --cflags --libs allegro-5 allegro_main-5 allegro_color-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_physfs-5 allegro_primitives-5 allegro_dialog-5)

all: $(NAME)

$(NAME):
	$(CPP) -o $(NAME) $(SRC) $(LIB) -shared $(CPPFLAGS) $(INCLUDE) 

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all