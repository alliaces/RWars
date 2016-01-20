#ifndef USOCKET_H_
#define USOCKET_H_

#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "ISocket.h"

#define SOCK_ADDR_SIZE sizeof(struct sockaddr_in)

class USocket : public ISocket
{
public:
  USocket(protocolId, int sock = -1, const void *addr = nullptr);
  ~USocket();

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

  struct sockaddr_in rcv_addr_;
  struct sockaddr_in addr_;
  int sock_;
};

#endif
