#ifndef ISOCKET_H_
#define ISOCKET_H_

#include <string>
#include <cstring>
#include <Protocol.h>
typedef unsigned short ushort;
typedef unsigned int uint;

#ifdef _WIN32
	# define SOCKET_WBLOCK		WSAEWOULDBLOCK
#elif __linux__
	# define SOCKET_WBLOCK		EWOULDBLOCK
#endif

class ISocket
{
public:
	virtual ~ISocket() { };

	virtual bool connect(const std::string&, ushort) = 0;
	virtual int send(char *, int) = 0;
	virtual int recv(char *, int) = 0;
	virtual bool bind(ushort) = 0;
	virtual ISocket *accept() = 0;
  virtual void close() = 0;

	virtual bool setBlocking(bool) = 0;
	virtual void setAddr(const void *) = 0;
	virtual void setRecvAddr(const void *) = 0;

	virtual bool isConnected() const = 0;
	virtual uint getId() const = 0;
	virtual const void *getAddr() const = 0;
	virtual const void *getRecvAddr() const = 0;
	virtual ushort getPort() const = 0;
	virtual const std::string& getAddress() const = 0;
	virtual protocolId getProtocol() const = 0;

	virtual int getLastError() const = 0;
protected:
	ushort port_;
	int last_error_;
	bool listening_;
	std::string address_;
	protocolId protocol_;
};

#endif
