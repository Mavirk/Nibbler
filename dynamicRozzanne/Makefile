NAME = nibbler

CPP			=	clang++ -std=c++11 -stdlib=libc++
CFLAGS		=	-Wall -Werror -Wextra 

LIB_FLAG	=	-dynamiclib -flat_namespace

SRC			=	main.cpp \
				Game.cpp \
				Snake.cpp
# ALLINC		= 	-I ~/.brew/include -L ~/.brew/lib -lallegro -lallegro_main
#OBJ = $(SRC:.cpp=.o)

#%.o: %.cpp 
	#@$(CXX) $(CFLAGS) $(SRC) -c $< -o $@

all: $(NAME)

$(NAME): dynamic
	$(CPP) $(CFLAGS) $(SRC)  -o $(NAME)

dynamic: sfml sdl2 ncur
	@cp sfml_lib/sfml.so ./
	@cp sdl_lib/sdl.so ./
	@cp ncur/ncur.so ./

alg:
	@make -C allegro_lib

ncur:
	@make -C ncur

sdl2:	
	@make -C sdl_lib

sfml:
	@make -C sfml_lib

clean:
	@make -C sdl_lib clean
	@make -C sfml_lib clean
	@make -C ncur clean
	@rm -rf $(OBJ)

fclean: clean
	# @rm *.so
	@rm -rf $(NAME)
	@make -C sdl_lib fclean
	@make -C sfml_lib fclean
	@make -C ncur fclean
	# @make -C allegro_lib fclean

re: fclean all