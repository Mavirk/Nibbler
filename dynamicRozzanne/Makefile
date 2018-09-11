NAME = nibbler

CPP			=	clang++ -std=c++11 -stdlib=libc++
CFLAGS		=	-Wall -Werror -Wextra 

LIB_FLAG	=	-dynamiclib -flat_namespace

SRC			=	main.cpp \
				Game.cpp \
				Snake.cpp

#OBJ = $(SRC:.cpp=.o)

#%.o: %.cpp 
	#@$(CXX) $(CFLAGS) $(SRC) -c $< -o $@

all: $(NAME)

$(NAME): dynamic
	$(CPP) $(CFLAGS) $(SRC) -o $(NAME)

dynamic: sfml sdl2 alg
	@cp allegro_lib/alg.so ./
	@cp sdl_lib/sdl.so ./
	@cp sfml_lib/sfml.so ./

alg:
	@make -C allegro_lib

sdl2:	
	@make -C sdl_lib

sfml:
	@make -C sfml_lib

clean:
	@make -C sdl_lib clean
	@make -C sfml_lib clean
	@make -C allegro_lib clean
	@rm -rf $(OBJ)

fclean: clean
	@rm *.so
	@rm -rf $(NAME)
	@make -C sdl_lib fclean
	@make -C sfml_lib fclean
	@make -C allegro_lib fclean

re: fclean all