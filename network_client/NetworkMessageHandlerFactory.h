#pragma once
#include "NetworkMessage.h"
#include "NetworkMessageHandler.h"
#include "AssingNetworkMessageHandler.h"

class NetworkMessageHandlerFactory
{
private: 
	SOCKET socket;
public:
	NetworkMessageHandlerFactory(SOCKET socket);
	~NetworkMessageHandlerFactory();
	NetworkMessageHandler* createNetworkMessageHandler(NetworkMessage* networkMessage);
};

