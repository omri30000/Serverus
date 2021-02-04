//
// Created by Omri Zaiman on 03/02/2021.
// Credit to Rob Tougher: https://tldp.org/LDP/LG/issue74/tougher.html
//

#ifndef COMMUNICATION_CLIENTSOCKET_H
#define COMMUNICATION_CLIENTSOCKET_H

#include "Socket.h"

class ClientSocket : private Socket
{
public:

    ClientSocket ( std::string host, int port );
    ~ClientSocket() override = default;

    const ClientSocket& operator << ( const vector<unsigned char>& ) const;
    const ClientSocket& operator >> ( std::string& ) const;

};

#endif //COMMUNICATION_CLIENTSOCKET_H
