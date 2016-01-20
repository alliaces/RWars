##
## Makefile for Makefile in /home/lelong_t/rendu/CPP/CPPTeck3/gomoku
## 
## Made by Théophile
## Login   <lelong_t@epitech.net>
## 
## Started on  Thu Nov 12 02:42:53 2015 Théophile
## Last update Fri Dec  4 01:35:01 2015 Théophile
##

ifeq ($(OS),Windows_NT)
	NAME		= AirEngine.dll
else
	NAME		= libAirEngine.so
endif


RM		= rm -f

CXX		= g++

SRCS		= 	src/AirWindow.cpp		\
			src/AirButton.cpp		\
			src/AirCheckBox.cpp		\
			src/AirTextBox.cpp		\
			src/AirText.cpp			\
			src/AirFont.cpp			\
			src/AirPicture.cpp		\
			src/AirSprite.cpp		\
			src/Vector2f.cpp		\
			src/Vector2u.cpp		\
			src/AirParticule.cpp		\
			src/AirParticuleGenerator.cpp	\
			src/AirMusic.cpp		\
			src/AirSound.cpp

OBJS		= $(SRCS:.cpp=.o)

INCLUDES	= -I lib/include -I include

ifeq ($(OS),Windows_NT)
	CXXFLAGS	= $(INCLUDES) -W -Wall -Wextra -Werror -pedantic -std=c++11
else
	CXXFLAGS	= $(INCLUDES) -W -Wall -Wextra -Werror -pedantic -std=c++11 -fPIC
endif

LIBS		= -L lib/lib/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CXX) -shared -o $(NAME) $(OBJS) $(CPPFLAGS) $(LIBS)
		mkdir -p bin
		cp $(NAME) test/bin
		mv $(NAME) bin

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) bin/$(NAME)

re:		fclean all
