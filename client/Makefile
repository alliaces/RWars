SRCS		=  src/main.cpp						\
		   src/UtilsSplit.cpp					\
		   src/ui/Ui.cpp					\
		   src/Network.cpp					\
		   src/ui/ResourceMediator.cpp				\
		   src/ui/SceneMediator.cpp				\
		   src/ui/scene/SplashScene.cpp				\
		   src/ui/scene/ConnectionScene.cpp			\
		   src/ui/scene/RoomScene.cpp				\
		   src/ui/scene/WaitScene.cpp				\
		   src/ui/scene/GameScene.cpp				\
		   src/ui/scene/ScoreScene.cpp				\
		   src/ui/Player.cpp					\
		   src/ui/Entity.cpp					\
		   src/Threads/ARunnableThread.cpp			\
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
		   common/srcs/Net/CNetManager.cpp

ifeq ($(OS), Windows_NT)
	SRCS	+= common/srcs/Sockets/WSocket.cpp
	SRCS	+= src/Threads/WThread.cpp
	SRCS	+= src/FileHandler/WindowsFileHandler.cpp
endif
ifeq ($(shell uname), Linux)
	SRCS	+= common/srcs/Sockets/USocket.cpp
	SRCS	+= src/Threads/UThread.cpp
	SRCS	+= src/FileHandler/LinuxFileHandler.cpp
endif

OBJS		=  $(SRCS:.cpp=.o)

NAME		=  client

CXX		=  g++

COMMON		=  -I common/includes -I common/includes/Sockets -I common/includes/PacketManager -I common/includes/Net

INCLUDES	=  $(COMMON) -I lib/libairengine/lib/include -I lib/libairengine/include/ -I includes -I includes/UI -I includes/Threads -I includes/FileHandler

CXXFLAGS	=  $(INCLUDES) -Wall -Wextra -std=c++11 -D__CLIENT__

LIBS		=  -L lib/libairengine/lib/lib/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -L lib/libairengine/bin/ -lAirEngine -L/lib64

ifeq ($(OS), Windows_NT)
	LIBS	+= -lws2_32
endif
ifeq ($(shell uname), Linux)
	LIBS	+= -lpthread
endif

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) -o $(NAME) $(OBJS) $(LIBS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
