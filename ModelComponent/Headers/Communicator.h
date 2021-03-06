//
// Created by Omri Zaiman on 03/02/2021.
//

#pragma once

#include "Event.h"
#include "ClientSocket.h"
#include "SocketException.h"

class Communicator{
    protected:
        ClientSocket openSocket(int port); // open with local host
        ClientSocket openSocket(string host, int port);
        int _port;
    public:
        Communicator(int port);
        ~Communicator() = default;

        void sendMessage(Event event);
};

