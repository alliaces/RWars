SRCS	=	   srcs/main.cpp					\
		   srcs/Core.cpp					\
		   srcs/Threads/ThreadsManager.cpp			\
		   srcs/Game/Game.cpp					\
		   srcs/Game/GameManager.cpp				\
		   srcs/Game/Client.cpp					\
		   srcs/Game/GameBuilder.cpp				\
		   srcs/Game/Map.cpp					\
		   srcs/Entities/AEntity.cpp				\
		   srcs/Entities/AShot.cpp				\
		   srcs/Entities/APlayer.cpp				\
		   srcs/Entities/AMonster.cpp				\
		   srcs/Entities/ABlock.cpp				\
		   srcs/Entities/AExplosion.cpp				\
		   srcs/Entities/ABonus.cpp				\
		   srcs/Entities/EntityManager.cpp			\
		   srcs/Entities/EntityContainer.cpp			\
		   common/srcs/Vector2.cpp				\
		   common/srcs/Vector3.cpp				\
		   common/srcs/ByteArray.cpp				\
		   common/srcs/PacketManager/PacketManager.cpp		\
		   common/srcs/PacketManager/PacketBuilder.cpp		\
		   common/srcs/PacketManager/APacket.cpp		\
		   common/srcs/PacketManager/SimplePacket.cpp		\
		   common/srcs/PacketManager/BytePacket.cpp		\
		   common/srcs/PacketManager/IntPacket.cpp		\
		   common/srcs/PacketManager/StringPacket.cpp		\
		   common/srcs/PacketManager/Vector2Packet.cpp		\
		   common/srcs/PacketManager/Vector3Packet.cpp		\
		   common/srcs/PacketManager/GameStartPacket.cpp	\
		   common/srcs/PacketManager/RoomInfoPacket.cpp		\
		   common/srcs/PacketManager/ReturnPacket.cpp		\
		   common/srcs/PacketManager/EntityCreatePacket.cpp	\
		   common/srcs/PacketManager/EntityUpdatePacket.cpp	\
		   common/srcs/Net/ServerNet.cpp			\
		   common/srcs/Net/ClientNet.cpp			\
		   common/srcs/Net/SNetManager.cpp			\
		   common/srcs/Net/CNetManager.cpp			\

ifeq ($(OS), Windows_NT)
	SRCS	+= common/srcs/Sockets/WSocket.cpp 	\
		   srcs/Threads/WThread.cpp		\
		   srcs/Threads/WMutex.cpp		\
		   srcs/Entities/WindowsFileHandler.cpp
endif
ifeq ($(shell uname), Linux)
	SRCS	+= common/srcs/Sockets/USocket.cpp	\
		   srcs/Threads/UThread.cpp		\
		   srcs/Threads/UMutex.cpp		\
		   srcs/Entities/LinuxFileHandler.cpp
endif

OBJS		=  $(SRCS:.cpp=.o)

NAME		=  server

CXX		=  g++

COMMON		=  -I common/includes -I common/includes/Sockets -I common/includes/PacketManager -I common/includes/Net

INCLUDES	=  $(COMMON) -I includes/Threads -I includes/ -I includes/Game -I includes/Entities

CXXFLAGS	=  $(INCLUDES) -Wall -Wextra -std=c++11

ifeq ($(OS), Windows_NT)
        LIBS     += -lws2_32
endif
ifeq ($(shell uname), Linux)
	LIBS	+=  -rdynamic -lpthread -ldl
endif

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) -o $(NAME) $(OBJS) $(LIBS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
