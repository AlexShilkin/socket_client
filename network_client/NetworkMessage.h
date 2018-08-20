#pragma once
#include "Message.h"

using namespace std;
#define ASSING_NETWORK_MESSAGE 1


class NetworkMessage
{
protected:
	char* data;
	int length;
	char* maskHeader;
	char* maskData;

public:
	virtual ~NetworkMessage() = 0 {};
	virtual char* getMessageFromNetwork() = 0;
	virtual int getSizeMessageFromNetwork() = 0;
	virtual NetworkMessage* getNetworkMessage(char* data) = 0;
	virtual int16_t getTypeMessage() = 0;
};

