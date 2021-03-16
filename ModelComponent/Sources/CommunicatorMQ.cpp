//
// Created by ofir on 16/03/2021.
//

#include "../Headers/CommunicatorMQ.h"

void CommunicatorMQ::sendMessage(Event event)
{
    vector<byte> vec = event.castToBinMessage();
    zmq::message_t msg;
    memcpy(msg.data(),vec.data(),vec.size());
    _socket.send(msg);
}

CommunicatorMQ::CommunicatorMQ(string file)
{
    _context = zmq::context_t(1);
    _socket = zmq::socket_t(_context,ZMQ_PULL);

    _socket.bind("ipc://"+file);
}


