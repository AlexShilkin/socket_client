#include "NetworkMessageHandlerFactory.h"



NetworkMessageHandlerFactory::NetworkMessageHandlerFactory(SOCKET socket)
{
	this->socket = socket;
}


NetworkMessageHandlerFactory::~NetworkMessageHandlerFactory()
{
}

NetworkMessageHandler* NetworkMessageHandlerFactory::createNetworkMessageHandler(NetworkMessage* networkMessage)
{
	NetworkMessageHandler* networkMessageHandler = nullptr;
	switch (networkMessage->getTypeMessage())
	{
	case ASSING_NETWORK_MESSAGE:
		AssingNetworkMessageHandler * assignNetworkMessageHandler = new AssingNetworkMessageHandler(this->socket);
		networkMessageHandler = assignNetworkMessageHandler;
		break;
	}
	return networkMessageHandler;
}