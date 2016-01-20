#ifndef WSOCKET_H_
#define WSOCKET_H_

#include <winsock2.h>
#include <windows.h>

#include "ISocket.h"

#define SOCK_ADDR_SIZE sizeof(SOCKADDR_IN)

class WSocket : public ISocket
{
public:
  WSocket(protocolId, SOCKET sock = INVALID_SOCKET, const void *addr = nullptr);
  ~WSocket();

  bool connect(const std::string&, ushort);
  int send(char *, int);
	int recv(char *, int);
  bool bind(ushort);
  ISocket *accept();
  void close();

  bool setBlocking(bool);
  void setAddr(const void *);
  void setRecvAddr(const void *);

  bool isConnected() const;
  uint getId() const;
  const void *getAddr() const;
	const void *getRecvAddr() const;
	ushort getPort() const;
	const std::string& getAddress() const;
	protocolId getProtocol() const;

	int getLastError() const;
private:
  bool lastError(int);
  bool connectTCP(const std::string&, ushort);
  bool connectUDP(const std::string&, ushort);
  bool bindTCP(ushort);
  bool bindUDP(ushort);

  SOCKET sock_;
	SOCKADDR_IN addr_;
  SOCKADDR_IN rcv_addr_;
};

#endif
