#pragma once
#include "NetworkMessage.h"
#include <cstring>
#pragma warning(disable:4996)


class BaseNetworkMessage :
	public NetworkMessage
{
protected:
	char* maskType();
	char* maskTypeHeader();
	char* maskTypeData();
public:
	BaseNetworkMessage();
	~BaseNetworkMessage();
	virtual char* getMessageFromNetwork();
	virtual int getSizeMessageFromNetwork();
	virtual NetworkMessage* getNetworkMessage(char* data);
	virtual int16_t getTypeMessage();
};

