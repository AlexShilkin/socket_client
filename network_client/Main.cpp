
#define GLEW_STATIC
#include <GL\glew.h>

#include <glfw3.h>

#include <WinSock2.h>

#include <stdio.h>
#include <iostream>"
#include "Events.h"
#include "Host.h"
#include "Sender.h"
#include "NetworkMessageFactory.h"
#include "QueueNetworkMessage.h"
#include "NetworkMessageHandler.h"
#include "NetworkMessageHandlerFactory.h"

using namespace std;
#pragma warning(disable : 4996)
#pragma comment(lib,"glew32s.lib")
#pragma comment(lib,"glfw3.lib")

Host * host;
QueueNetworkMessage *queueNetworkMessage;
HANDLE threadReceive;
HANDLE threadComputation;
unsigned int idTreadReceive;
unsigned int idTreadComputation;


////////////
NetworkMessage* ReceiveMessage(SOCKET socket) {
	NetworkMessage* networkMessage;
	NetworkMessageFactory networkMessageFactory = NetworkMessageFactory();

	char *headerMessage;
	char *dataMessage;

	headerMessage = RecvData(socket, MESSAGE_MESSAGE_SIZE_HEADER);

	int16_t version;
	int16_t flag;
	int16_t idHost;
	int32_t length;
	unpack((unsigned char*)headerMessage, "hhhl ", &version, &flag, &idHost, &length);
	
	if (length > 0) {
		dataMessage = RecvData(socket, length);
		return networkMessageFactory.createNetworkMessage(flag, dataMessage);
	}

	return nullptr;
}
	
UINT WINAPI ReceiveThread(void* pvParam) {
	DWORD dwResult = 0;
	HANDLE eventNewMessage = GetEventNewMessage();
	HANDLE eventPushMessageInQueue = GetEventPushMessageInQueue();
	HANDLE eventCloseReceiveThread = GetEventCloseReceiveThread();
	for (;;) {
		if (WAIT_OBJECT_0 == WaitForSingleObject(eventCloseReceiveThread, 0)) {
			break;
		}
		NetworkMessage* networkMessage = ReceiveMessage(host->getSocketHost());
		if (networkMessage != nullptr) {
			queueNetworkMessage->push(networkMessage);
			SetEvent(eventPushMessageInQueue);
		}
	}
	return dwResult;
}
	
UINT WINAPI ComputationThread(void *pvParam) {

	HANDLE eventPushMessageInQueue = GetEventPushMessageInQueue();
	for (;;) {
		if (WAIT_OBJECT_0 == WaitForSingleObject(eventPushMessageInQueue, 0)) {
			NetworkMessage* networkNessage = queueNetworkMessage->pop();
			ResetEvent(eventPushMessageInQueue);
			NetworkMessageHandler* networkMessageHandler; 
			NetworkMessageHandlerFactory networkMessageHandlerFactory = NetworkMessageHandlerFactory(host->getSocketHost());
			networkMessageHandler = networkMessageHandlerFactory.createNetworkMessageHandler(networkNessage);
			networkMessageHandler->action(networkNessage);
		}

	}
	return 1;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// ����� ������������ �������� ESC, �� ������������� �������� WindowShouldClose � true, 
	// � ���������� ����� ����� ���������
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
	queueNetworkMessage = new QueueNetworkMessage();
	char* nameClient = "Alex";
	host = new Host(nameClient);
	host->connect("192.168.1.56", 5150);
	if (host->getError() == 0) {
		//start receiveThread
		threadReceive = (HANDLE)_beginthreadex(NULL, 0, ReceiveThread, 0, 0, &idTreadReceive);
		//start computationThread
		threadComputation = (HANDLE)_beginthreadex(NULL, 0, ComputationThread, 0, 0, &idTreadComputation);
	}
	
	WaitForSingleObject(threadReceive, INFINITE);
	WaitForSingleObject(threadComputation, INFINITE);
	closesocket(host->getSocketHost());
	WSACleanup();
	
	//end socket

	/*Comment
	
	//������������� GLFW
	glfwInit();
	//��������� GLFW
	//�������� ����������� ��������� ������ OpenGL. 
	//�������� 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//��������
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//��������� �������� ��� �������� ��������� ��������
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//���������� ����������� ��������� ������� ����
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "network_game", nullptr, nullptr);
	if (window == nullptr)
	{
		cout << "Filied to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}


	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);


	//callback key
	glfwSetKeyCallback(window, key_callback);
	GLfloat vertices[] = {
	-0.5f,-0.5f,0.0f,
	0.5f,-0.5f,0.0f,
	0.5f,0.5f,0.0f,
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);


	//main loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		//begin render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//end render
		glfwSwapBuffers(window);
	}
	*/
}

