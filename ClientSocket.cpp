//
// Created by Omri Zaiman on 03/02/2021.
// Credit to Rob Tougher: https://tldp.org/LDP/LG/issue74/tougher.html
//

// Implementation of the ClientSocket class

#include "ClientSocket.h"
#include "SocketException.h"

ClientSocket::ClientSocket ( std::string host, int port )
{
    if (!Socket::create())
    {
        throw SocketException ( "Could not create client socket." );
    }

    if (!Socket::connect(host,port))
    {
        throw SocketException ( "Could not bind to port." );
    }
}


const ClientSocket& ClientSocket::operator << ( const vector<unsigned char>& vec ) const
{
    if ( ! Socket::send ( vec ) )
    {
        throw SocketException ( "Could not write to socket." );
    }

    return *this;
}


const ClientSocket& ClientSocket::operator >> ( std::string& s ) const
{
    if ( ! Socket::recv ( s ) )
    {
        throw SocketException ( "Could not read from socket." );
    }

    return *this;
}