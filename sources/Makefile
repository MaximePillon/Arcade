##
## Makefile for libsfml in /home/loens_g/rendu/TEK2/CPP/cpp_arcade
## 
## Made by loens_g
## Login   <loens_g@epitech.net>
## 
## Started on  Thu Apr  6 21:08:23 2017 loens_g
## Last update Fri Apr  7 19:44:06 2017 loens_g
##

INCLUDE		= 	-I../includes

RM		=	rm -rf

CPPFLAGS	+=	$(INCLUDE)

CPPFLAGS	+=	-W -Wextra -Wall

LDFLAGS		+=	-ldl

CC		=	g++

DEBUG		?=	0

ifeq	($(DEBUG), 1)
	CC	=	g++
	CPPFLAGS	+=	-g -ggdb3
endif

NAME		=	../arcade

SRCS		=	launcher/Launcher.cpp \
			main.cpp

OBJS		=	 $(SRCS:.cpp=.o)


all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) -o $(NAME) $(LDFLAGS) $(OBJS)

%.o:	%.cpp
	$(CC) -c -o $@ $< $(CPPFLAGS)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME) $(CLI)

re:	fclean
	@$(MAKE) all

.PHONY:	 all clean fclean re

-include	$(DEPS)
