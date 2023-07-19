NAME=texture.a

FILES=   main  vectors utils utils2 shader_utils

OBJ=$(FILES:=.o)

FLAGS = -Wall -Wextra #-Werror

LINKS= gcc -I /usr/local/include -O3 $(FILES:=.c) -L /usr/local/lib \
    -lmlx -framework OpenGL -framework Appkit

all: $(NAME)

$(NAME):
	$(LINKS)  
	
#ar rcs $(NAME) $(OBJ) 

clean:
	rm -rf $(OBJ) 
fclean:
	rm -rf $(OBJ) $(NAME)

re: fclean all