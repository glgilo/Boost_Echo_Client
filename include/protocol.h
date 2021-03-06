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
    ConnectionHandler* connectionHandler_;
    clientDataBase clientDB;
    bool socketTermination = false;

public:
    ~protocol()= default;
    protocol(const protocol&)= default;
    protocol &operator=(const protocol&)= default;
    protocol(ConnectionHandler*);
    void process(vector<string>);
    void proccesServerLine(vector<string>);
    string splitAndGetSecondWord (string,char);
    string discoverType(string);
    bool contains(vector<string>&, string&);
    vector<string> stringToVector (string&, char);
    string myBooksByTopic(string&);
    bool isSocketTermination() const;
    clientDataBase &getClientDb();
    string bookRemoveSpace(vector<string>);
    string bookAddSpace(string);
    string splitAndGetFirstWord (string,char);

};


#endif //BOOST_ECHO_CLIENT_PROTOCOL_H
