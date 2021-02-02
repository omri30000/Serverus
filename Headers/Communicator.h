#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <map>

#include "IRequestHandler.h"
#include "WSAInitializer.h"
#include "RequestHandlerFactory.h"

const int PORT = 2019;
using std::map;

class Communicator
{
public:
	static Communicator* CreateCommunicator(RequestHandlerFactory* factory);
	void startHandleRequest();
	~Communicator();

protected:
	void bindAndListen();
	void handleNewClient(SOCKET clientSock);
	void acceptClient();
	map<SOCKET, IRequestHandler*> _mClients; 
	SOCKET _serverSocket; //the listening socket
	RequestHandlerFactory* m_handlerFactory;

private:
	Communicator(RequestHandlerFactory* factory);
	static Communicator* s_m_communicator;

	WSAInitializer _wsa;
};