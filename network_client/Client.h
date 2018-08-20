#pragma once
class Client;
class ClientDestroyer {
private:
	Client* p_instance;
public:
	~ClientDestroyer();
	void initialize(Client* p);
};
class Client
{
private:
	static Client* p_instance;
	static ClientDestroyer destroyer;
	static int _id;
	static char* _name;
protected:
	Client() {}
	Client(const Client&);
	Client& operator= (Client&);
	~Client() {}
	friend class ClientDestroyer;
public:
	static Client & getInstance();
	static void setId(int id);
	static void setName(char* name);
	static int getId();
	static char* getName();
};

