#include "USocket.h"

USocket::USocket(protocolId protocol, int sock, const void *addr)
{
  sock_ = sock;
  port_ = 0;
  address_ = "";
  last_error_ = 0;
  listening_ = false;
  protocol_ = protocol;
  this->setAddr(nullptr);
  this->setRecvAddr(addr);
}

USocket::~USocket()
{
  this->close();
}

bool USocket::connect(const std::string& address, ushort port)
{
  bool r;

  if ((r = (protocol_ == protocolId::TCP ?
    this->connectTCP(address, port) :
    this->connectUDP(address, port)
  )))
  {
    address_ = address;
    port_ = port;
  }
  return (r);
}

int USocket::send(char *data, int size)
{
  int len = ::sendto(sock_, data, size, 0, (struct sockaddr *)&rcv_addr_, sizeof(rcv_addr_));
  last_error_ = errno;
  return (len);
}

int USocket::recv(char *data, int size)
{
  unsigned int addrSize = sizeof(rcv_addr_);
  int len = ::recvfrom(sock_, data, size, 0, (struct sockaddr *)&rcv_addr_, &addrSize);
  last_error_ = errno;
  return (len);
}

bool USocket::bind(ushort port)
{
  bool r;

  if ((r = (protocol_ == protocolId::TCP ?
    this->bindTCP(port) :
    this->bindUDP(port)
  )))
  {
    port_ = port;
    listening_ = true;
  }
  return (r);
}

ISocket *USocket::accept()
{
  if (listening_ && protocol_ == protocolId::TCP)
  {
    int sock;
    struct sockaddr_in client;
    unsigned int clientSize = sizeof(client);

    if ((sock = ::accept(sock_, (struct sockaddr *)&client, &clientSize)) < 0)
      return (nullptr);
    this->last_error_ = errno;
    return (new USocket(protocolId::TCP, sock));
  }
  return (nullptr);
}

void USocket::close()
{
  if (sock_ != -1)
  {
    ::shutdown(sock_, SHUT_RDWR);
    ::close(sock_);
  }
}

bool USocket::setBlocking(bool blocking)
{
  int flag;

  if (!this->isConnected())
  {
    return (false);
  }
  if ((flag = fcntl(sock_, F_GETFL, 0)) < 0)
  {
    return (this->lastError(errno));
  }
  flag = blocking ? (flag&~O_NONBLOCK) : (flag|O_NONBLOCK);
  if (fcntl(sock_, F_SETFL, flag) == 0)
    return (true);
    return (this->lastError(errno));
}

void USocket::setAddr(const void *addr)
{
	if (addr)
	{
		std::memcpy(&addr_, addr, sizeof(addr_));
		return;
	}
	std::memset(&addr_, 0, sizeof(addr_));
}

void USocket::setRecvAddr(const void *addr)
{
	if (addr)
	{
		std::memcpy(&rcv_addr_, addr, sizeof(rcv_addr_));
		return;
	}
	std::memset(&rcv_addr_, 0, sizeof(rcv_addr_));
}

bool USocket::isConnected() const
{
  return (sock_ != -1);
}

uint USocket::getId() const
{
  return ((uint)sock_);
}

const void *USocket::getAddr() const
{
	return (&addr_);
}

const void *USocket::getRecvAddr() const
{
	return (&rcv_addr_);
}

ushort USocket::getPort() const
{
  return (port_);
}

const std::string& USocket::getAddress() const
{
  return (address_);
}

protocolId USocket::getProtocol() const
{
  return (protocol_);
}

int USocket::getLastError() const
{
  return (last_error_);
}

bool USocket::lastError(int e)
{
  last_error_ = e;
  return (false);
}

bool USocket::connectTCP(const std::string& address, ushort port)
{
  struct hostent *hostinfo = NULL;

  if ((sock_ = ::socket(AF_INET, SOCK_STREAM, 0)) < 0)
    return (this->lastError(errno));
  if ((hostinfo = ::gethostbyname(address.c_str())) == NULL)
    return (this->lastError(errno));
  rcv_addr_.sin_addr = *(struct in_addr *)hostinfo->h_addr;
  rcv_addr_.sin_port = ::htons(port);
  rcv_addr_.sin_family = AF_INET;
  if (::connect(sock_, (struct sockaddr *)&rcv_addr_, sizeof(struct sockaddr)) < 0)
    return (this->lastError(errno));
  return (true);
}

bool USocket::connectUDP(const std::string& address, ushort port)
{
  int udp_size = 2 * 1024 * 1024;
  struct hostent *hostinfo = NULL;

  if ((sock_ = ::socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    return (this->lastError(errno));
  if ((hostinfo = ::gethostbyname(address.c_str())) == NULL)
    return (this->lastError(errno));
  if (::setsockopt(sock_, SOL_SOCKET, SO_RCVBUF, &udp_size, sizeof(udp_size)) == -1)
    return (this->lastError(errno));
  rcv_addr_.sin_addr = *(struct in_addr *)hostinfo->h_addr;
  rcv_addr_.sin_port = ::htons(port);
  rcv_addr_.sin_family = AF_INET;
  return (true);
}

bool USocket::bindUDP(ushort port)
{
  int i = 1;
  int udp_size = 2 * 1024 * 1024;

  if ((sock_ = ::socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    return (this->lastError(errno));
  addr_.sin_addr.s_addr = ::htonl(INADDR_ANY);
  addr_.sin_family = AF_INET;
  addr_.sin_port = ::htons(port);
  if (::setsockopt(sock_, SOL_SOCKET, SO_RCVBUF, &udp_size, sizeof(udp_size)) == -1)
    return (this->lastError(errno));
  if (::setsockopt(sock_, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i)) == -1)
    return (this->lastError(errno));
  if (::bind(sock_, (struct sockaddr *)&addr_, sizeof(addr_)) < 0)
    return (this->lastError(errno));
  return (true);
}

bool USocket::bindTCP(ushort port)
{
  int i = 1;

  if ((sock_ = ::socket(AF_INET, SOCK_STREAM, 0)) < 0)
    return (this->lastError(errno));
  addr_.sin_addr.s_addr = ::htonl(INADDR_ANY);
  addr_.sin_family = AF_INET;
  addr_.sin_port = ::htons(port);
  if (::setsockopt(sock_, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i)) == -1)
    return (this->lastError(errno));
  if (::bind(sock_, (struct sockaddr *)&addr_, sizeof(addr_)) < 0)
    return (this->lastError(errno));
  if (listen(sock_, 1024) < 0)
    return (this->lastError(errno));
  return (true);
}
