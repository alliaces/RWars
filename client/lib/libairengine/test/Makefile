##
## Makefile for Makefile in /home/lelong_t/rendu/CPP/CPPTeck3/gomoku
## 
## Made by Théophile
## Login   <lelong_t@epitech.net>
## 
## Started on  Thu Nov 12 02:42:53 2015 Théophile
## Last update Thu Nov 26 15:00:23 2015 Théophile
##

NAME		= test

RM		= rm -f

CXX		= g++

SRCS		= 	src/main.cpp	\
			src/MainMenu.cpp

OBJS		= $(SRCS:.cpp=.o)

INCLUDES	= -I ../lib/include -I include -I ../include

CXXFLAGS	= $(INCLUDES) -W -Wall -Wextra -Werror -pedantic -std=c++11

LIBS		= -L ../lib/lib/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -L ../bin -lAirEngine

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CXX) -o $(NAME) $(OBJS) $(CPPFLAGS) $(LIBS)
		mkdir -p bin
		mv $(NAME) bin

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) bin/$(NAME)

re:		fclean all
