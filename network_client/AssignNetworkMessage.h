#pragma once
#include "Message.h"
#include "BaseNetworkMessage.h"

#define SERVER_ID_HOST 0


class AssignNetworkMessage : public BaseNetworkMessage
{
private:
	int16_t idClient;

public:
	AssignNetworkMessage();
	AssignNetworkMessage(int16_t idClient);
	~AssignNetworkMessage();

	char* getMessageFromNetwork();
	int getSizeMessageFromNetwork();
	NetworkMessage* getNetworkMessage(char* data);
	int16_t getTypeMessage();
	int16_t getIdClinet();
};

