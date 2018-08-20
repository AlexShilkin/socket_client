#pragma once
#include "Message.h"
#include "NetworkBase.h"
#include "NetworkMessage.h"
class Sender
{
public:
	Sender();
	~Sender();
	int Send(SOCKET socket, NetworkMessage* message);
};

