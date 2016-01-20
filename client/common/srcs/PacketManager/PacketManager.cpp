#include "PacketManager.h"

PacketManager::PacketManager() { }

PacketManager::~PacketManager() { }

void PacketManager::addPacket(IPacket *packet)
{
  if (packet)
  {
    packets_.push(packet);
  }
}

void PacketManager::appendBinary(char *data, int size, int id)
{
  data_[id].append(data, size);
}

//Return 0 on error, 1 on packet handled, and 2 when there is no more packets to process.
int PacketManager::handlePacket(int id)
{
  if (data_[id].getSize() >= PACKET_SIZE)
  {
    int size = *((int *)data_[id].getBytes());
    if (size < HEADER_SIZE) //The packet is corrupted or not correct.
      return (0);
    if (data_[id].getSize() >= size)//If the packet is complete.
    {
      this->addPacket(builder_.build(data_[id].getBytes(), id));
      data_[id].erase(0, size);
      return (1);
    }
  }
  return (2);
}

//That method return 'false' when a client/packet is corrupted.
bool PacketManager::handle(int id)
{
  int r;
  while ((r = this->handlePacket(id)) == 1);
  return (r > 0);
}

void PacketManager::clear(int id)
{
  data_[id].clear();
}

IPacket *PacketManager::pollPacket()
{
  IPacket *packet = nullptr;

  if (!packets_.empty())
  {
    packet = packets_.front();
    packets_.pop();
  }
  return (packet);
}
