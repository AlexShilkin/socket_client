#pragma once
#include "NetworkMessage.h"


class NetworkMessageHandler
{
public:
	virtual ~NetworkMessageHandler()=0 {};
	virtual void action(NetworkMessage* networkMessage) = 0;
};

