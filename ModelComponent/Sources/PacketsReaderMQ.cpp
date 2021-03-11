//
// Created by ofir on 11/03/2021.
//

#include "../Headers/PacketsReaderMQ.h"
#include <iostream>
//constructors
PacketsReaderMQ::PacketsReaderMQ() : PacketsReaderMQ("/tmp/fifo-pipe1")
{

}

PacketsReaderMQ::PacketsReaderMQ(string file) : PacketsReader(file)
{
    _context = zmq::context_t(1);
    _socket = zmq::socket_t(_context,ZMQ_PULL);

    _socket.bind("ipc://"+file);


}

Packet PacketsReaderMQ::getNextPacket() {
    zmq::message_t msg;
    _socket.recv(&msg);

    string data = msg.to_string();

    std::vector<string> parts(1);
    int index = 0;
    for (int i = 0; i <data.size(); ++i)
    {
        if(data[i] == ',')
        {
            parts.push_back("");
            index++;
        }
        else
        {
            parts[index] += data[i];
        }

    }

    //std::cout<<msg.to_string()<<std::endl;
    return Packet(parts,0);
}
