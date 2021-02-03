//
// Created by Omri Zaiman on 03/02/2021.
//

#pragma once

#include "Event.h"

class Communicator {
    protected:
        void openSocket();

    public:
        Communicator();
        ~Communicator() = default;

        void sendMessage(Event event);
};

