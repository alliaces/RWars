#include "Ui.h"
#include "CNetManager.h"
#include "uistruct.h"
#include "Packet.h"
#include "RoomInfoPacket.h"
#include "StringPacket.h"
#include "ReturnPacket.h"
#include "SimplePacket.h"
#include "BytePacket.h"
#include "GameStartPacket.h"
#include "EntityCreatePacket.h"
#include "EntityUpdatePacket.h"
#include "Vector3Packet.h"
#include "Vector2Packet.h"
#include "IntPacket.h"
#include "Utils.h"

Ui::Ui()
{
}

Ui::~Ui()
{
	delete this->resourceMediator_;
	delete this->sceenMediator_;
}

void *Ui::run(void *)
{
  this->window_ = new AirWindow("rtype", Vector2u(1280, 720));
  this->resourceMediator_ = new ResourceMediator();
  this->sceenMediator_ = new SceneMediator(this, this->window_, this->resourceMediator_);
  this->window_->SetScene(this->sceenMediator_->getSceneByName("SplashScene"));
  while (this->window_->IsOpen())
    {
      this->window_->Update();
    }
  return (NULL);
}

void Ui::OnEvent(UiEvent event, void* data)
{
  switch (event)
    {
    case ONCONNECT :
      std::cout << "[\033[32mINFO\033[0m] Connect to " << ((Param*)data)->ip << ":" << ((Param*)data)->port << std::endl;
      if (dynamic_cast<CNetManager*>(TCPlis)->connect(((Param*)data)->ip,atoi(((Param*)data)->port.c_str())))
	{
	  TCPlis->doEvent(Event::PACKET, new StringPacket(Packet::AUTH, "bidon"));
	  dynamic_cast<IUiListener*>(window_->GetScene())->OnEvent(UiEvent::ONRETCONNECT, NULL);
	}
      else
	dynamic_cast<IUiListener*>(window_->GetScene())->OnEvent(UiEvent::ONRETCONNECT, (void*)"Server unreachable.");
      break;
    case ONJOINROOM :
      TCPlis->doEvent(Event::PACKET, new StringPacket(Packet::ROOM_JOIN, (char*)data));
      break;
    case ONCREATEROOM :
      TCPlis->doEvent(Event::PACKET, new StringPacket(Packet::ROOM_CREATE, (char*)data));
      break;
    case ONLEAVEROOM :
      TCPlis->doEvent(Event::PACKET, new SimplePacket(Packet::ROOM_LEAVE));
      break;
    case ONREFRESHROOM :
      TCPlis->doEvent(Event::PACKET, new SimplePacket(Packet::ROOM_REFRESH));
      break;
    case ONREADY :
      TCPlis->doEvent(Event::PACKET, new BytePacket(Packet::READY, 1));
      break;
    case ONPOSITIONUPDATE :
      UDPlis->doEvent(Event::PACKET, new Vector3Packet(Packet::UPDATE_POS, Vector3(0,0,*(int*)data)));
      break;
    case ONSHOT :
      UDPlis->doEvent(Event::PACKET, new SimplePacket(Packet::PLAYER_SHOT));
      break;
    case ONSENDCREATEENTITY :
      UDPlis->doEvent(Event::PACKET, new EntityCreatePacket(*(int*)data, Vector3(0,0,0), Vector2(0,0), 0, ""));
      break;
    case ONSENDROOMBACK :
      UDPlis->doEvent(Event::PACKET, new SimplePacket(Packet::ROOM_BACK));
      break;
    default:
      break;
    }
}

void Ui::setUDPListener(IEventListener *lis)
{
  this->UDPlis = lis;
}

void Ui::setTCPListener(IEventListener *lis)
{
  this->TCPlis = lis;
}

int Ui::doEvent(Event::id id, void* data)
{
  if (id == Event::PACKET)
    {
      switch (((IPacket*)data)->getOpcode())
	{
	case Packet::ROOM_INFO:
	  std::cout << "[\033[32mINFO\033[0m] Receive room : " << ((RoomInfoPacket*)data)->getRoom().c_str() << " : " << \
	    (((RoomInfoPacket*)data)->isAvailable() ? "Available" : "Enavailable") << std::endl;
	  if (((RoomInfoPacket*)data)->isAvailable())
	    dynamic_cast<IUiListener*>(window_->GetScene())->OnEvent(UiEvent::ONRECEIVEROOM, (void*)(((RoomInfoPacket*)data)->getRoom() + " " +  Utils::to_string(((RoomInfoPacket*)data)->getNumberOfPlayers()) + "/4").c_str());
	  else
	    dynamic_cast<IUiListener*>(window_->GetScene())->OnEvent(UiEvent::ONRECEIVEWRONGROOM, (void*)(((RoomInfoPacket*)data)->getRoom() + " " +  Utils::to_string(((RoomInfoPacket*)data)->getNumberOfPlayers()) + "/4").c_str());
	  break;
	case Packet::RETURN:
	  if (((ReturnPacket*)data)->getClientOpcode() == Packet::ROOM_JOIN)
	    {
	      std::cout << "[\033[32mINFO\033[0m] Join room" << std::endl;
	      if (((ReturnPacket*)data)->getError() == "")
		dynamic_cast<IUiListener*>(window_->GetScene())->OnEvent(UiEvent::ONRETJOINROOM, NULL);
	      else
		std::cout << "[\033[31mERROR\033[0m] Join error : " << ((ReturnPacket*)data)->getError() << std::endl;
	    }
	  else if (((ReturnPacket*)data)->getClientOpcode() == Packet::ROOM_CREATE)
	    {
	      std::cout << "[\033[32mINFO\033[0m] Create room" << std::endl;
	      if (((ReturnPacket*)data)->getError() != "")
		{
		  dynamic_cast<IUiListener*>(window_->GetScene())->OnEvent(UiEvent::ONRETCREATEROOMERROR, (void*)((ReturnPacket*)data)->getError().c_str());
		  std::cout << "[\033[31mERROR\033[0m] Create error : " << ((ReturnPacket*)data)->getError() << std::endl;
		}
	    }
	  break;
	case Packet::HAS_JOINED:
	  std::cout << "[\033[32mINFO\033[0m] Player join room" << std::endl;
	  dynamic_cast<IUiListener*>(window_->GetScene())->OnEvent(UiEvent::PLAYERJOIN, (void*)(((StringPacket*)data)->getString().c_str()));
	  break;
	case Packet::HAS_LEFT:
	  std::cout << "[\033[32mINFO\033[0m] Player left room" << std::endl;
	  dynamic_cast<IUiListener*>(window_->GetScene())->OnEvent(UiEvent::PLAYERQUIT, (void*)(((StringPacket*)data)->getString().c_str()));
	  break;
	case Packet::START_GAME:
	  std::cout << "[\033[32mINFO\033[0m] Game start" << std::endl;
	  dynamic_cast<IUiListener*>(window_->GetScene())->OnEvent(UiEvent::STARTGAME, NULL);
	  std::cout << "[\033[32mINFO\033[0m] UDP Connection : " << ((GameStartPacket*)data)->getIp() << ":" << ((GameStartPacket*)data)->getPort() << std::endl;
	  dynamic_cast<CNetManager*>(UDPlis)->connect(((GameStartPacket*)data)->getIp(),((GameStartPacket*)data)->getPort());
	  UDPlis->doEvent(Event::PACKET, new StringPacket(Packet::AUTH, "bidon"));
	  break;
	case Packet::ENTITY_CREATE:
	  {
	    ParamEntity* param = new ParamEntity;
	    param->id = ((EntityCreatePacket*)data)->getEntityId();
	    param->x = ((EntityCreatePacket*)data)->getPosition().x;
	    param->y = ((EntityCreatePacket*)data)->getPosition().y;
	    param->rot = ((EntityCreatePacket*)data)->getPosition().z;
	    param->size_x = ((EntityCreatePacket*)data)->getScale().x;
	    param->size_y = ((EntityCreatePacket*)data)->getScale().y;
	    param->id_sprite = ((EntityCreatePacket*)data)->getSpriteId();
	    param->name = ((EntityCreatePacket*)data)->getName();
	    dynamic_cast<IUiListener*>(window_->GetScene())->OnEvent(UiEvent::ONCREATEENTITY, (void*)param);
	    break;
	  }
	case Packet::ENTITY_UPDATE:
	  {
	    ParamEntity* param = new ParamEntity;
	    param->id = ((EntityUpdatePacket*)data)->getEntityId();
	    param->x = ((EntityUpdatePacket*)data)->getPosition().x;
	    param->y = ((EntityUpdatePacket*)data)->getPosition().y;
	    param->rot = ((EntityUpdatePacket*)data)->getPosition().z;
	    param->id_sprite = ((EntityUpdatePacket*)data)->getSpriteId();
	    dynamic_cast<IUiListener*>(window_->GetScene())->OnEvent(UiEvent::ONUPDATEENTITY, (void*)param);
	    break;
	  }
	case Packet::ENTITY_DESTROY:
	  {
	    ParamEntity* param = new ParamEntity;
	    param->id = ((IntPacket*)data)->getInt();
	    dynamic_cast<IUiListener*>(window_->GetScene())->OnEvent(UiEvent::ONDESTROYENTITY, (void*)param);
	    break;
	  }
	case Packet::ENTITY_POINT:
	  {
	    dynamic_cast<IUiListener*>(window_->GetScene())->OnEvent(UiEvent::ONSCORE, (void*)&((Vector2Packet*)data)->getPosition().y);
	    break;
	  }
	case Packet::ENTITY_LIFE:
	  {
	    dynamic_cast<IUiListener*>(window_->GetScene())->OnEvent(UiEvent::ONUPDATELIFE, (void*)&((Vector2Packet*)data)->getPosition().y);
	    break;
	  }
	case Packet::FINAL_SCORE:
	  {
	    dynamic_cast<IUiListener*>(window_->GetScene())->OnEvent(UiEvent::ONFINALSCORE, (void*)&((Vector2Packet*)data)->getPosition().y);
	    break;
	  }
	}
    }
  else if (id == Event::CLIENT_DISCONNECT)
    {
      if (window_ && window_->GetScene() && dynamic_cast<IUiListener*>(window_->GetScene()))
	{
	  dynamic_cast<IUiListener*>(window_->GetScene())->OnEvent(UiEvent::DISCONNECT, NULL);
	}
    }
  return (0);
}
