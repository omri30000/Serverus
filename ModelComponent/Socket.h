//
// Created by Omri Zaiman on 03/02/2021.
// Credit to Rob Tougher: https://tldp.org/LDP/LG/issue74/tougher.html
//

#ifndef COMMUNICATION_SOCKET_H
#define COMMUNICATION_SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <arpa/inet.h>
#include <iostream>

const int MAXHOSTNAME = 200;
const int MAXCONNECTIONS = 5;
const int MAXRECV = 500;

using byte = unsigned char;
using std::vector;

class Socket
{
public:
    Socket();
    virtual ~Socket();

    // Server initialization
    bool create();
    bool bind ( const int port );
    bool listen() const;
    bool accept ( Socket& ) const;

    // Client initialization
    bool connect ( const std::string host, const int port );

    // Data Transimission
    bool send ( const vector<byte> ) const;
    int recv ( std::string& ) const;


    void set_non_blocking ( const bool );

    bool is_valid() const { return m_sock != -1; }

private:

    int m_sock;
    sockaddr_in m_addr;
};


#endif
