#include "Host.h"

Host::Host()
{
}

Host::Host(char* nameClient)
{
	this->nameClient = nameClient;
	socketVersion = MAKEWORD(2, 2);
	WSAStartup(socketVersion, &wsaData);
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	error = 0;
	if (clientSocket == SOCKET_ERROR) {
		error = GetLastError();
		Print("Unable to create socket");
		WSACleanup();
	}
	else {
		Print("Create socket");
	}
}


Host::~Host()
{
	closesocket(clientSocket);
	WSACleanup();
}

void Host::connect(char * addressServer, int port)
{
	if (error == 0) {
		serverHost = { 0 };
		serverHost.sin_family = AF_INET;
		serverHost.sin_addr.S_un.S_addr = inet_addr(addressServer);
		serverHost.sin_port = htons(port);
		int retVal = Connect(clientSocket, serverHost);
		if (retVal == SOCKET_ERROR) {
			error = GetLastError();
			Print("Unable to connect");
		}
		else {
			Print("Connection made sucessfully");
		}
	}
}

void Host::disconnect()
{

}

SOCKET Host::getSocketHost()
{
	return clientSocket;
}

int Host::getError()
{
	return error;
}

char * Host::getName()
{
	return nameClient;
}
