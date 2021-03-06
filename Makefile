##
## Makefile for makefile in /home/loens_g/rendu/TEK2/CPP/cpp_arcade
## 
## Made by loens_g
## Login   <loens_g@epitech.net>
## 
## Started on  Thu Apr  6 21:49:10 2017 loens_g
## Last update Sun Apr  9 20:20:24 2017 Hugo SOSZYNSKI
##

all:
	make -C sources/protocol/

graph:
	make -C sources/sfml/
	make -C sources/OpenGL/
	make -C externLibs/myncurses/
	make -C sources/ncurses/
	make -C sources/snake/
	make -C sources/Centipede/
	make -C sources/

clean:
	make -C sources/sfml/ clean
	make -C sources/OpenGL/ clean
	make -C externLibs/myncurses/ clean
	make -C sources/ncurses/ clean
	make -C sources/snake/ clean
	make -C sources/Centipede/ clean
	make -C sources/ clean

fclean:
	make -C sources/sfml/ fclean
	make -C sources/OpenGL/ fclean
	make -C externLibs/myncurses/ fclean
	make -C sources/ncurses/ fclean
	make -C sources/snake/ fclean
	make -C sources/Centipede/ fclean
	make -C sources/ fclean

re:
	make -C sources/protocol/ re
