
#define GLEW_STATIC
#include <GL/glew.h>
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
	// Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true, 
	// и приложение после этого закроется
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
#ifdef ONLY_NETWORK
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
#endif // ONLY_NETWORK

	
	
	//Инициализация GLFW
	glfwInit();
	//Настройка GLFW
	//Задается минимальная требуемая версия OpenGL. 
	//Мажорная 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//Минорная
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Установка профайла для которого создается контекст
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Выключение возможности изменения размера окна
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
	
	
	//Shaders
	//vertex
	const GLchar* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
	"}\0";

	//создение вершинного шейдера
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//привязка исходного кода шейдера и компиляция
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//проверка компиляции
	GLint successVertex;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successVertex);

	if (!successVertex) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FALIED\n"
			<< infoLog
			<< endl;
	}
	//end vertex

	//fragment

	const GLchar* fragmentShaderSource = "#version 330 core\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";
	//создение фрагментного шейдера
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//привязка исходного кода шейдера и компиляция
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//проверка компиляции
	GLint successFragment;
	GLchar infoLogFragment[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFragment);

	if (!successFragment) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLogFragment);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FALIED\n"
			<< infoLogFragment
			<< endl;
	}

	//end fragment

	//Shader Programm
	//создение программы
	GLuint shaderProgramm;
	shaderProgramm = glCreateProgram();
	//соединения шейдеров с программой
	glAttachShader(shaderProgramm, vertexShader);
	glAttachShader(shaderProgramm, fragmentShader);
	glLinkProgram(shaderProgramm);
	//проверка shader programm
	GLint successShaderProgramm;
	GLchar log[512];
	glGetProgramiv(shaderProgramm, GL_LINK_STATUS, &successShaderProgramm);
	if (!successShaderProgramm) {
		glGetProgramInfoLog(shaderProgramm, 512, NULL, log);
		cout << "ERROR::SHADER::PROGRAMM::COMPILATION_FALIED\n"
			<< log
			<< endl;
	}


	//удаление шейдеров
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//end Shader Programm

	//end Shaders
	
	//Связывание вершинных атрибутов
	
	//Vertexs

	GLfloat vertices[] = {
		-0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		0.5f,0.5f,0.0f,
	};

	//end Vertexs

	//VBO VAO
	GLuint vao;
	glGenVertexArrays(1, &vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);

	
	//end VBO VAO


	glBindVertexArray(vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	




	//main loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		//begin render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		
		//использование программы
		glUseProgram(shaderProgramm);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		//end render
		glfwSwapBuffers(window);
	}
	
}

