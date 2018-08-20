#pragma once
#include "NetworkBase.h"

class SocketProvider;
class SocketProviderDestroyer {
private:
	SocketProvider * p_instance;
public:
	SocketProviderDestroyer();
	void initialize(SocketProvider* p);
};
class SocketProvider
{
private:
	static SocketProvider* p_instance;
	static SocketProviderDestroyer destroyer;
	static SOCKET socketSend;
	static SOCKET socketRecv;
protected:
	SocketProvider() {}
	SocketProvider(const SocketProvider&);
	SocketProvider& operator=(SocketProvider&);
	friend class SocketProviderDestroyer;
public:
	static SocketProvider& getInstance();
	static void setSocketSend(SOCKET socket);
	static void setSocketRecv(SOCKET socket);
	static SOCKET getSocketSend();
	static SOCKET getSocketRecv();
};

