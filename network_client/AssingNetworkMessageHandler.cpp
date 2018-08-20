#include "AssingNetworkMessageHandler.h"



AssingNetworkMessageHandler::AssingNetworkMessageHandler(SOCKET socket)
{
	this->socket = socket;
}


AssingNetworkMessageHandler::~AssingNetworkMessageHandler()
{
}

void AssingNetworkMessageHandler::action(NetworkMessage* networkMessage)
{
	AssignNetworkMessage* assignNetworkMessage = (AssignNetworkMessage*)networkMessage;
	AssignNetworkMessage* newAssignNetworkMessage = new AssignNetworkMessage(assignNetworkMessage->getIdClinet());
	Sender sender = Sender();
	sender.Send(socket, newAssignNetworkMessage);
}


