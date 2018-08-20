#include "SocketProvider.h"


SocketProvider::SocketProvider(const SocketProvider &)
{
}

SocketProvider & SocketProvider::operator=(SocketProvider &)
{
	return *this;
}

SocketProvider & SocketProvider::getInstance()
{
	if (!p_instance) {
		p_instance = new SocketProvider();
		destroyer.initialize(p_instance);
	}
	return *p_instance;
}

void SocketProvider::setSocketSend(SOCKET socket)
{
	socketSend = socket;
}

void SocketProvider::setSocketRecv(SOCKET socket)
{
	socketRecv = socket;
}

SOCKET SocketProvider::getSocketSend()
{
	return socketSend;
}

SOCKET SocketProvider::getSocketRecv()
{
	return socketRecv;
}

SocketProviderDestroyer::SocketProviderDestroyer()
{
	delete p_instance;
}

void SocketProviderDestroyer::initialize(SocketProvider * p)
{
	p_instance = p;
}
