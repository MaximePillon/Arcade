##
## Makefile for ncurses in /home/soszyn_h/Documents/Projects/MyNcursesPP
## 
## Made by Hugo SOSZYNSKI
## Login   <hugo.soszynski@epitech.eu>
## 
## Started on  Wed Apr  5 09:57:14 2017 Hugo SOSZYNSKI
## Last update Fri Apr  7 14:41:29 2017 Hugo SOSZYNSKI
##

INCLUDE		=	-I./includes

LIB_PATH	=	../

RM		=	rm -rf

CPPFLAGS	+=	$(INCLUDE)

CPPFLAGS	+=	-MD -MP

CPPFLAGS	+=	-W -Wall -Wextra -lncurses

CC		=	g++

AR		=	ar rc

DEBUG		?=	0

ifeq	($(DEBUG), 1)
	CC		=	g++
	CPPFLAGS	+=	-g -ggdb3
endif

NAME		=	libmyncurses.a

SRCS		=	$(shell cat ./sources.mk)

OBJS		=	$(SRCS:.cpp=.o)

DEPS		=	$(SRCS:.cpp=.d)


all:		$(NAME)

$(NAME):	$(OBJS)
		$(AR) $(NAME) $(OBJS)
		mv $(NAME) $(LIB_PATH)

%.o:		%.cpp
		$(CC) -c -o $@ $< $(CPPFLAGS)

clean:
		$(RM) $(OBJS) $(DEPS)

fclean:		clean
		$(RM) $(LIB_PATH)$(NAME)

re:		fclean
		@$(MAKE) all

.PHONY:	 all clean fclean re

-include	$(DEPS)
