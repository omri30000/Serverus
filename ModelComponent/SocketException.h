//
// Created by omrizaiman on 03/02/2021.
//

#ifndef COMMUNICATION_SOCKETEXCEPTION_H
#define COMMUNICATION_SOCKETEXCEPTION_H

#include <string>

class SocketException
{
public:
    SocketException ( std::string s ) : m_s ( s ) {};
    ~SocketException () = default;

    std::string description() { return m_s; }

private:

    std::string m_s;

};

#endif //COMMUNICATION_SOCKETEXCEPTION_H
