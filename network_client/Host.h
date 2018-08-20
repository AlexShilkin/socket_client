#pragma once
#include "NetworkBase.h"
#include <stdio.h>
#include "Events.h"
#include "Utils.h"
#include "Message.h"


class Host
{
private:
	char* nameClient;
	SOCKET clientSocket;
	SOCKADDR_IN serverHost;
	WORD socketVersion;
	WSADATA wsaData;
	int error;
public:
	Host();
	Host(char* nameClient);
	~Host();
	
	void connect(char *addressServer, int port);
	
	void disconnect();

	SOCKET getSocketHost();

	int getError();

	char* getName();
};

