#ifndef STRING_PACKET_H_
#define STRING_PACKET_H_

#include <string>
#include "APacket.h"

class StringPacket : public APacket
{
public:
  StringPacket(int, const std::string& = "");
  ~StringPacket();

  void setString(const std::string&);
  const std::string& getString() const;

  char *build();
private:
  std::string str_;
};

#endif
