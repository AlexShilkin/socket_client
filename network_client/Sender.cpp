#include "Sender.h"


Sender::Sender()
{
}


Sender::~Sender()
{
}

int Sender::Send(SOCKET socket, NetworkMessage * message)
{
	int countSendData=SendData(socket,
		message->getMessageFromNetwork(),
		message->getSizeMessageFromNetwork());
	return countSendData;
}
