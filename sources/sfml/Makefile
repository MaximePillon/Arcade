##
## Makefile for libsfml in /home/loens_g/rendu/TEK2/CPP/cpp_arcade
## 
## Made by loens_g
## Login   <loens_g@epitech.net>
## 
## Started on  Thu Apr  6 21:08:23 2017 loens_g
## Last update Fri Apr  7 18:10:47 2017 Hugo SOSZYNSKI
##

INCLUDE		= 	-I../../includes

RM		=	rm -rf

CPPFLAGS	+=	$(INCLUDE)

CPPFLAGS	+=	-W -Wextra -Wall -fPIC -lsfml-system -lsfml-window -lsfml-graphics

LDFLAGS		+=	-shared -Wl,--no-allow-shlib-undefined /usr/lib64/libsfml-graphics.so /usr/lib64/libsfml-window.so /usr/lib64/libsfml-system.so

CC		=	g++

DEBUG		?=	0

ifeq	($(DEBUG), 1)
	CC	=	g++
	CPPFLAGS	+=	-g -ggdb3
endif

NAME		=	libsfml.so

SRCS		=	SfmlGraph.cpp


OBJS		=	 $(SRCS:.cpp=.o)


all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) -o $(NAME) $(LDFLAGS) $(OBJS)
	mv $(NAME) ../../lib

%.o:	%.cpp
	$(CC) -c -o $@ $< $(CPPFLAGS)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) ../../lib/$(NAME) $(CLI)

re:	fclean
	@$(MAKE) all

.PHONY:	 all clean fclean re

-include	$(DEPS)
