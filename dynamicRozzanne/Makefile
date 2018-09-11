NAME=				nibbler

RM=					rm -f

#LIBRARIES_NIBBLER=	-ldl -export-dynamic

INCLUDES=			-I ~/.brew/include

CPPFLAGS=			-Wall -Wextra -Werror $(LIBRARIES_NIBBLER) -g

SRC=				main.cpp \
					Game.cpp \
					Snake.cpp


OBJ=				$(SRC:.cpp=.o)

LIBRARY_SFML=		sfml.so

LIBRARY_SDL=		sdl.so

LIBRARY_NCURSES=	ncur.so

SFML_SRC=			sfml_lib/SFML.cpp \
					Snake.cpp

NCURSES_SRC=		ncur/ncurses.cpp \
					Snake.cpp

SDL_SRC=			sdl_lib/SDL.cpp \
					Snake.cpp

all:				$(LIBRARY_SFML) $(LIBRARY_SDL) $(LIBRARY_NCURSES) $(NAME)

$(LIBRARY_SFML):
					g++ -o $(LIBRARY_SFML) $(SFML_SRC) -shared -fPIC -L ~/.brew/lib -lsfml-system -lsfml-window -lsfml-graphics $(CPPFLAGS) $(INCLUDES)

$(LIBRARY_SDL):
					g++ -o $(LIBRARY_SDL) $(SDL_SRC) -L ~/.brew/lib -lSDL2 -lSDL2_ttf -shared -fPIC -Wall -Wextra -Werror $(INCLUDES)

$(LIBRARY_NCURSES):
					g++ -o $(LIBRARY_NCURSES) $(NCURSES_SRC) -shared -fPIC -lncurses -Wall -Wextra -Werror $(INCLUDES)

$(NAME):			$(OBJ)
					g++ -o $(NAME) $(OBJ) $(CPPFLAGS)

clean:
					$(RM) $(OBJ) $(SFML_OBJ) $(SDL_OBJ) $(NCURSES_OBJ)

fclean:				clean
					$(RM) $(NAME) $(LIBRARY_NCURSES) $(LIBRARY_SDL) $(LIBRARY_SFML)

re:					clean fclean all