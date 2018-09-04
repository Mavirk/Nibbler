NAME = snake

SRC = main.cpp \
		srcs/LibClassSDL.cpp \

CPP = g++ -std=c++11 -stdlib=libc++
CFLAGS = -Wall -Werror -Wextra
CFLAGS += -I include/ -I ~/.brew/include

#$(shell pkg-config --cflags --libs sdl2)
LIB = -L ~/.brew/lib -lSDL2
#LIB += -lncurses

all: Lib1.so
	$(CPP) $(CFLAGS) $(SRC) -o $(NAME) $(LIB)
	@echo [INFO] $@ "Completed successfully."

Lib1.so:
	$(CPP) -dynamiclib -flat_namespace srcs/LibClassSDL.cpp -o Lib1.so
	@echo [INFO] $@ "Shared library made successfully."

clean:
	@rm -f *.o *.so
	@echo "[INFO] Objects removed!"

fclean: clean
	@rm -rf $(NAME)
	@echo "[INFO] $(NAME) removed!"

re: fclean all

.PHONY: all clean fclean re