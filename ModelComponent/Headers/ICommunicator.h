//
// Created by ofir on 16/03/2021.
//
#pragma once
class ICommunicator
        {
protected:

public:
    ICommunicator();
    ~ICommunicator() = default;

    virtual void sendMessage(Event event) = nullptr;
    //void recvMessage() = nullptr;
};

