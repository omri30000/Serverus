//
// Created by ofir on 11/03/2021.
//

#pragma once
#include <zmq.hpp>
#include <string>
#include "PacketsReader.h"

class PacketsReaderMQ : PacketsReader
{
    protected:
        zmq::context_t _context;
        zmq::socket_t _socket;


    public:
        PacketsReaderMQ();
        PacketsReaderMQ(string file);
        virtual Packet getNextPacket();

};


