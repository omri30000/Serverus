//
// Created by ofir on 16/03/2021.
//

#pragma once

#include <zmq.hpp>
#include "ICommunicator.h"
#include "Event.h"

class CommunicatorMQ : public ICommunicator
{
protected:
    zmq::context_t _context;
    zmq::socket_t _socket;

public:
    CommunicatorMQ(string file);
    //or by port
    //CommunicatorMQ(int port);

    ~CommunicatorMQ() = default;

    virtual void sendMessage(Event event);

};


