##
## Makefile for libsfml in /home/loens_g/rendu/TEK2/CPP/cpp_arcade
## 
## Made by loens_g
## Login   <loens_g@epitech.net>
## 
## Started on  Thu Apr  6 21:08:23 2017 loens_g
## Last update Fri Apr  7 10:51:51 2017 loens_g
##

INCLUDE		= 	-I../../includes -I/usr/include/freetype2/ -I/usr/include/libpng16

RM		=	rm -rf

CPPFLAGS	+=	$(INCLUDE)

CPPFLAGS	+=	-W -Werror -Wextra -Wall -fPIC -lglfw -IGL -IGLEW -IGLU -L/usr/local/lib -lfreetype -l/usr/include/freetype2/ -l/usr/include/libpng16

LDFLAGS		+=	-shared

CC		=	g++

DEBUG		?=	0

ifeq	($(DEBUG), 1)
	CC	=	g++
	CPPFLAGS	+=	-g -ggdb3
endif

NAME		=	libOpenGL.so

SRCS		=	OpenGLGraph.cpp


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
