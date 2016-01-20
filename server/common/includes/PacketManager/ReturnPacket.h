#ifndef RETURN_PACKET_H_
#define RETURN_PACKET_H_

#include <string>
#include "APacket.h"

class ReturnPacket : public APacket
{
public:
  ReturnPacket(int opcode, const std::string& = "");
  ~ReturnPacket();

  void setClientOpcode(int);
  void setError(const std::string&);
  int getClientOpcode() const;
  const std::string& getError() const;

  char *build();
private:
  int clientOpcode_;
  std::string error_;
};

#endif
