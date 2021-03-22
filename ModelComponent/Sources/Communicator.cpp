//
// Created by Omri Zaiman on 03/02/2021.
//

#include "../Headers/Communicator.h"

/*
Constructor
*/
Communicator::Communicator(int port)
{
    _port = port;
}

/*
The function will open a conversation socket with the defender
input: The port to connect to
output: the conversation socket
*/
ClientSocket Communicator::openSocket(int port)
{
    // Connect to the Defender
    ClientSocket sock("localhost", port);

    return sock;
}

/*
The function will open a conversation socket with the defender
input: The ip address and port to connect to
output: the conversation socket
*/
ClientSocket Communicator::openSocket(string host, int port)
{
    // Connect to the Defender
    ClientSocket sock(host, port);

    return sock;
}

/*
The function will send an event to the defender
input: the event to be sent
output: none
*/
void Communicator::sendMessage(Event event)
{
    try{
        ClientSocket sock = this->openSocket(_port); // Defender's port, get from config file
        sock << event.castToBinMessage();
    }
    catch (SocketException& e)
    {
        std::cout << "Exception was caught: " << e.description() << "\n";
    }
    catch (...)
    {
        std::cout << "Exception was caught while sending message \n";
    }
}