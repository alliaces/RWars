RM		= rm -f

CPP		= g++

SRC		= Sources/$(NAME).cpp			\
		  ../srcs/Entities/AExplosion.cpp	\
		  ../srcs/Entities/APlayer.cpp		\
		  ../srcs/Entities/AMonster.cpp		\
		  ../srcs/Entities/ABlock.cpp		\
		  ../srcs/Entities/ABonus.cpp		\
		  ../srcs/Entities/AShot.cpp		\
		  ../srcs/Entities/AEntity.cpp		\
		  ../common/srcs/Vector2.cpp		\
		  ../srcs/Game/Map.cpp			\
		  ../srcs/Entities/EntityContainer.cpp


OBJ		= $(SRC:.cpp=.o)

ifeq ($(OS), Windows_NT)
    INCLUDE	+= -O0 -g3 -fmessage-length=0
endif
ifeq ($(shell uname), Linux)
	INCLUDE	+= -fPIC
endif

COMMON  = $(INCLUDE) -I ../common/includes -I ../common/includes/Sockets -I ../common/includes/PacketManager -I ../common/includes/Net

INCLUDES =  $(COMMON) -I ../includes/Threads -I ../includes/ -I ../includes/Game -I ../includes/Entities

CXXFLAGS = $(INCLUDES) -I Sources/Includes -std=c++11 -W -Wall -Wextra

all: clean NAME

NAME: $(OBJ)
ifeq ($(shell uname), Linux)
	mkdir -p Linux
	$(CPP) -shared -o Linux/$(NAME).so $(OBJ)
endif
ifeq ($(OS), Windows_NT)
	mkdir -p Win32
	$(CPP) -shared -g -o Win32/$(NAME).dll $(OBJ)
endif

clean:
ifeq ($(shell uname), Linux)
	$(RM) Linux/$(NAME).so
endif
ifeq ($(OS), Windows_NT)
	$(RM) Win32/$(NAME).dll
endif
	$(RM) $(OBJ)
