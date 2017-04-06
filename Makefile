##
## Makefile for makefile in /home/loens_g/rendu/TEK2/CPP/cpp_arcade
## 
## Made by loens_g
## Login   <loens_g@epitech.net>
## 
## Started on  Thu Apr  6 21:49:10 2017 loens_g
## Last update Thu Apr  6 21:52:49 2017 loens_g
##

all:
	make -C sources/sfml/
	make -C sources/OpenGL/
	make -C sources/ncurses/

clean:
	make -C sources/sfml/ clean
	make -C sources/OpenGL/ clean
	make -C sources/ncurses/ clean

fclean:
	make -C sources/sfml/ fclean
	make -C sources/OpenGL/ fclean
	make -C sources/ncurses/ fclean

re:
	make -C sources/sfml/ re
	make -C sources/OpenGL/ re
	make -C sources/ncurses/ re
