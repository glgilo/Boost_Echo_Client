//
// Created by lavih@wincs.cs.bgu.ac.il on 13/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_SOCKETREADER_H
#define BOOST_ECHO_CLIENT_SOCKETREADER_H

#include <connectionHandler.h>
#include <protocol.h>
using namespace std;

class socketReader {
private:
    ConnectionHandler *connectionHandler_;
    protocol *protocol_;
    vector<string> fromFrame;
public:
    socketReader(ConnectionHandler *connectionHandler, protocol *protocol);
    void operator()();
};


#endif //BOOST_ECHO_CLIENT_SOCKETREADER_H
