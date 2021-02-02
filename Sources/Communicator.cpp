#include "../Headers/Communicator.h"
#include <exception>
#include <thread>
#include <string>
#pragma comment (lib, "ws2_32.lib")

#include "RequestInfo.h"
#include "ConversationUtils.h"
#include "JsonResponsePacketSerializer.h"

Communicator* Communicator::s_m_communicator = nullptr;

// ----------------Constructor ----------------
Communicator::Communicator(RequestHandlerFactory* factory)
{
	this->m_handlerFactory = factory;
	_serverSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_serverSocket == INVALID_SOCKET)
	{
		throw std::exception("Can't create Socket");
	}
}

/*

*/
Communicator* Communicator::CreateCommunicator(RequestHandlerFactory* factory)
{
	if (s_m_communicator == nullptr) // check whether a server already exists
	{
		s_m_communicator = new Communicator(factory);
	}

	return s_m_communicator;
}

/*
This function handles the communication with the clietns
Input:None
Output:None
*/
void Communicator::startHandleRequest()
{
	bindAndListen();

	while (true)
	{
		acceptClient();
	}
}

/*

*/
Communicator::~Communicator()
{
	if (s_m_communicator != nullptr)
	{
		delete s_m_communicator;
	}
}

/*
This function binds the server socket to the requested port, and start listening
Input:None
Output:None
*/
void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 }; //initialize all memebers to 0
	sa.sin_port = htons(PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = 0;//IFACE

	if (::bind(this->_serverSocket, (struct sockaddr*) & sa, sizeof(sa)) == SOCKET_ERROR)
	{
		throw std::exception("Can't bind server socket");
	}

	if (::listen(this->_serverSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		throw std::exception("Can't listens to clients' requests");
	}
}
/*
This function handles the conversation with the client
Input:clientSock -- The socket with the client
Output:None
*/
void Communicator::handleNewClient(SOCKET clientSock)
{

	const int ID_LENGTH = 1; // number of bytes the ID takes
	const int SIZE_LENGTH = 4; // number of bytes the content's size takes
	const int LOGOUT = 101;
	char id[ID_LENGTH];
	char size[SIZE_LENGTH];
	char* reqContent = nullptr;
	int sizeInt = 0;
	int idInt = 0;
	
	map<SOCKET, IRequestHandler*>::iterator client = this->_mClients.find(clientSock); // iterartor for place in comunicator map
	if (client == this->_mClients.end())
	{
		std::string s = "Error was occurred";
		s += std::to_string(clientSock);
		throw std::exception(s.c_str());
	}


	// a one timed message to client
	if (send(clientSock, "HELLO", 5, 0) == INVALID_SOCKET)
	{
		throw std::exception("Can't send message to client :<");
	}

	while (true) 
	{
		try
		{
			ConversationUtils::receiveFromSocket(clientSock, id, ID_LENGTH);
			idInt = ConversationUtils::castByteToInt(ConversationUtils::castBuffToVector(id, ID_LENGTH));

			ConversationUtils::receiveFromSocket(clientSock, size, SIZE_LENGTH);
			sizeInt = ConversationUtils::castByteToInt(ConversationUtils::castBuffToVector(size, SIZE_LENGTH));

			reqContent = new char[sizeInt]; // have to be deleted
			ConversationUtils::receiveFromSocket(clientSock, reqContent, sizeInt);
		}
		catch (std::exception e)
		{
			if (reqContent != nullptr)
			{
				delete[] reqContent;
			}
			std::cout << e.what();

			return;
		}

		RequestInfo req(idInt,ConversationUtils::castBuffToVector(reqContent,sizeInt),sizeInt);

		delete[] reqContent;
		reqContent = nullptr;

		vector<unsigned char> finalBuffer;
		if (client->second->isRequestRelevant(req)) 	
		{
			RequestResult reqResult = client->second->handleRequest(req);

			//change RequestHandler
			if (reqResult._newHandler)//if succeeded
			{
				delete client->second;
				client->second = reqResult._newHandler;
			}
			finalBuffer = reqResult._buffer;
			//send response to client
		}
		else
		{
			finalBuffer = ConversationUtils::buildErrorResponse("You can't access this action\n");
		}
		try
		{
			ConversationUtils::sendToSocket(clientSock, finalBuffer);
		}
		catch (std::exception er)
		{
			std::cout << er.what() << std::endl; 
		}
	}
}


/*
This funtion wait until a client connects and acccepts it
Input:None
Output:None
*/
void Communicator::acceptClient()
{
	SOCKET clientSocket = accept(this->_serverSocket, NULL, NULL); //wait until client arrives and accepts it.
	
	if (clientSocket == INVALID_SOCKET)
	{
		throw std::exception("Can't accept client");
	}

	//insert to clients list
	this->_mClients.insert(std::pair<SOCKET, IRequestHandler*>(clientSocket,(IRequestHandler*)this->m_handlerFactory->createLoginRequestHandler()));

	//call to managing thread
	std::thread clientThread(&Communicator::handleNewClient, this, clientSocket);
	clientThread.detach();

}


