#include "Client.h"

Client* Client::p_instance = 0;
ClientDestroyer Client::destroyer;

Client::Client(const Client &)
{
}

Client& Client::operator=(Client &)
{
	return *this;
}

Client& Client::getInstance()
{
	if (!p_instance) {
		p_instance = new Client();
		destroyer.initialize(p_instance);
	}
	return *p_instance;
}

void Client::setId(int id)
{
	_id = id;
}

void Client::setName(char * name)
{
	_name = name;
}

int Client::getId()
{
	return _id;
}

char * Client::getName()
{
	return _name;
}

ClientDestroyer::~ClientDestroyer()
{
	delete p_instance;
}

void ClientDestroyer::initialize(Client * p)
{
	p_instance = p;
}
