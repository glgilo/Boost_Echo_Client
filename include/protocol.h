//
// Created by igale@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_PROTOCOL_H
#define BOOST_ECHO_CLIENT_PROTOCOL_H

#include "connectionHandler.h"
#include "clientDataBase.h"

using namespace std;

class protocol {
private:
    ConnectionHandler connectionHandler_;
    clientDataBase clientDB;

public:
    void process(vector<string>);
};


#endif //BOOST_ECHO_CLIENT_PROTOCOL_H
