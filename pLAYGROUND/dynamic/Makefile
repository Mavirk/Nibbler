CXX = g++

NAME = nibbler

CFLAGS = -Wall -Werror -Wextra 

LIB_FLAG = -dynamiclib -flat_namespace

SRC = 	main.cpp game.cpp 

#OBJ = $(SRC:.cpp=.o)

#%.o: %.cpp 
	#@$(CXX) $(CFLAGS) $(SRC) -c $< -o $@

all: $(NAME)

$(NAME): sfml sdl2 
	@cp sdl_lib/sdl.so ./
	@cp sfml_lib/sfml.so ./
	@$(CXX) $(CFLAGS) main.cpp game.cpp -o $(NAME)

sdl2:
	
	@make -C sdl_lib

sfml:
	@make -C sfml_lib

#example: src/main.cpp libcircle.so
#	@g++ -o example src/main.cpp -ldl

clean:
	@make -C sdl_lib clean
	@make -C sfml_lib clean
	@rm -rf $(OBJ)

fclean: clean
	@rm *.so
	@rm -rf $(NAME)
	@make -C sdl_lib fclean
	@make -C sfml_lib fclean

re: fclean all