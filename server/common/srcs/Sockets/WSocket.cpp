#include "WSocket.h"

WSocket::WSocket(protocolId protocol, SOCKET sock, const void *addr)
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

WSocket::~WSocket()
{
  this->close();
}

bool WSocket::connect(const std::string& address, ushort port)
{
  bool r;
	WSADATA wsadata;

	if (::WSAStartup(MAKEWORD(2, 2), &wsadata) == SOCKET_ERROR)
		return (this->lastError(::WSAGetLastError()));
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

int WSocket::send(char *data, int size)
{
	WSABUF buff;
	DWORD sentBytes;

	buff.len = size;
	buff.buf = data;
	if (::WSASendTo(sock_, &buff, 1, &sentBytes, 0, (SOCKADDR *)&addr_, sizeof(SOCKADDR), NULL, NULL) == SOCKET_ERROR)
	{
		this->lastError(::WSAGetLastError());
		return (-1);
	}
	this->lastError(::WSAGetLastError());
	return (sentBytes);
}

int WSocket::recv(char *data, int size)
{
	WSABUF buff;
	DWORD flags;
	DWORD sentBytes;
	int addrSize = sizeof(SOCKADDR);

	flags = 0;
	buff.len = size;
	buff.buf = data;
	if (::WSARecvFrom(sock_, &buff, 1, &sentBytes, &flags, (SOCKADDR *)&addr_, &addrSize, NULL, NULL) == SOCKET_ERROR)
	{
    this->lastError(::WSAGetLastError());
		return (-1);
	}
	this->lastError(::WSAGetLastError());
	return (sentBytes);
}

bool WSocket::bind(ushort port)
{
  bool r;
	WSADATA wsadata;

	if (::WSAStartup(MAKEWORD(2, 2), &wsadata) == SOCKET_ERROR)
		return (this->lastError(::WSAGetLastError()));
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

ISocket *WSocket::accept()
{
  if (listening_ && protocol_ == protocolId::TCP)
  {
		SOCKET sock;
    struct sockaddr_in client;
		int clientSize = sizeof(client);

		if ((sock = ::WSAAccept(sock_, (SOCKADDR *) &client, &clientSize, NULL, 0)) == INVALID_SOCKET)
      return (nullptr);
    return (new WSocket(protocolId::TCP, sock));
  }
  return (nullptr);
}

//Take care of ::WSACleanup(). Call it only when EVERYTHING is finished !
void WSocket::close()
{
  if (sock_ != INVALID_SOCKET)
  {
    ::shutdown(sock_, SD_BOTH);
  	::closesocket(sock_);
  }
}

bool WSocket::setBlocking(bool blocking)
{
	unsigned long mode = blocking ? 0 : 1;

	if (!this->isConnected())
		return (false);
  if (::ioctlsocket(sock_, FIONBIO, &mode) == 0)
		return (true);
	return (this->lastError(::GetLastError()));
}

void WSocket::setAddr(const void *addr)
{
	if (addr)
	{
		std::memcpy(&addr_, addr, sizeof(addr_));
		return;
	}
	std::memset(&addr_, 0, sizeof(addr_));
}

void WSocket::setRecvAddr(const void *addr)
{
	if (addr)
	{
		std::memcpy(&rcv_addr_, addr, sizeof(rcv_addr_));
		return;
	}
	std::memset(&rcv_addr_, 0, sizeof(rcv_addr_));
}

bool WSocket::isConnected() const
{
	return (sock_ != INVALID_SOCKET);
}

uint WSocket::getId() const
{
  return ((uint)sock_);
}

const void *WSocket::getAddr() const
{
	return (&addr_);
}

const void *WSocket::getRecvAddr() const
{
	return (&rcv_addr_);
}

ushort WSocket::getPort() const
{
	return (port_);
}

const std::string& WSocket::getAddress() const
{
	return (address_);
}

protocolId WSocket::getProtocol() const
{
	return (protocol_);
}

int WSocket::getLastError() const
{
	return (last_error_);
}

bool WSocket::lastError(int e)
{
	last_error_ = e;
	return (false);
}

bool WSocket::connectTCP(const std::string& address, ushort port)
{
	u_short nport;
	HOSTENT *hostinfo = NULL;

	if ((sock_ = ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0)) == INVALID_SOCKET)
		return (this->lastError(::WSAGetLastError()));
	if ((hostinfo = ::gethostbyname(address.c_str())) == NULL)
		return (this->lastError(::WSAGetLastError()));
	addr_.sin_addr = *(IN_ADDR *)hostinfo->h_addr;
	::WSAHtons(sock_, port, &nport);
	addr_.sin_port = nport;
	addr_.sin_family = AF_INET;
	if (::WSAConnect(sock_, (SOCKADDR *)&addr_, sizeof(SOCKADDR), NULL, NULL, NULL, NULL) == SOCKET_ERROR)
		return (this->lastError(::WSAGetLastError()));
	return (true);
}

bool WSocket::connectUDP(const std::string& address, ushort port)
{
	u_short nport;
	HOSTENT *hostinfo = NULL;
	int udp_size = 2 * 1024 * 1024;

	if ((sock_ = ::WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, 0)) == INVALID_SOCKET)
		return (this->lastError(::WSAGetLastError()));
	if (::setsockopt(sock_, SOL_SOCKET, SO_RCVBUF, (const char *)&udp_size, sizeof(udp_size)) == -1)
		return (this->lastError(::WSAGetLastError()));
	if ((hostinfo = ::gethostbyname(address.c_str())) == NULL)
		return (this->lastError(::WSAGetLastError()));
	addr_.sin_addr = *(IN_ADDR *)hostinfo->h_addr;
	::WSAHtons(sock_, port, &nport);
	addr_.sin_port = nport;
	addr_.sin_family = AF_INET;
	return (true);
}

bool WSocket::bindTCP(ushort port)
{
	u_short nport;

	if ((sock_ = ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0)) == INVALID_SOCKET)
		return (this->lastError(::WSAGetLastError()));
	addr_.sin_family = AF_INET;
  addr_.sin_addr.s_addr = INADDR_ANY;
	::WSAHtons(sock_, port, &nport);
	addr_.sin_port = nport;
	if (::bind(sock_, (SOCKADDR *)&addr_, sizeof(addr_)) == SOCKET_ERROR)
		return (this->lastError(::WSAGetLastError()));
	if (::listen(sock_, SOMAXCONN) == SOCKET_ERROR)
		return (this->lastError(::WSAGetLastError()));
	return (true);
}

bool WSocket::bindUDP(ushort port)
{
  u_short nport;
	int udp_size = 2 * 1024 * 1024;

	if ((sock_ = ::WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, 0)) == INVALID_SOCKET)
		return (this->lastError(::WSAGetLastError()));
	addr_.sin_family = AF_INET;
  addr_.sin_addr.s_addr = INADDR_ANY;
	::WSAHtons(sock_, port, &nport);
	addr_.sin_port = nport;
	if (::setsockopt(sock_, SOL_SOCKET, SO_RCVBUF, (const char *)&udp_size, sizeof(udp_size)) == -1)
		return (this->lastError(::WSAGetLastError()));
	if (::bind(sock_, (SOCKADDR *)&addr_, sizeof(addr_)) == SOCKET_ERROR)
		return (this->lastError(::WSAGetLastError()));
	return (true);
}
