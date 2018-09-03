CXX =			g++

NAME =			sdl.so

CFLAGS =		-Wall -Werror -Wextra

LIB_FLAG =		-shared -fPIC

SRC =			IGraphics.cpp sdl.cpp

OBJ =			$(SRC:.cpp=.cpp.o)



%.cpp.o: %.cpp
	@$(CXX) $(CFLAGS) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(CFLAGS) $(LIB_FLAG) -o $(NAME) $(OBJ)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

