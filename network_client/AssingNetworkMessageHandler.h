#pragma once
#include "NetworkMessageHandler.h"
#include "AssignNetworkMessage.h"
#include "Sender.h"
#include "Client.h"

class AssingNetworkMessageHandler : public NetworkMessageHandler
{
private: 
	SOCKET socket;
public:
	AssingNetworkMessageHandler(SOCKET socket);
	~AssingNetworkMessageHandler();
	void action(NetworkMessage* networkMessage);
};

