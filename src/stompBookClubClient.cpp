//
// Created by igale@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include "stompBookClubClient.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <socketReader.h>
#include <thread>
#include "connectionHandler.h"
#include "protocol.h"
#include "keyboardReader.h"

using namespace std;


int main() {
    vector<string> temp;
    do {
        cout << "please login" <<endl;
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        temp.clear();
        stringstream start(line);
        string tempWord;
        while (getline(start, tempWord, ' ')) {
            temp.push_back(tempWord);
        }
    }
    while(temp.at(0) != "login");

    ConnectionHandler connectionHandler(temp.at(1),7777);
    protocol aProtocol(&connectionHandler);
    connectionHandler.connect();

    keyboardReader keyboardReader(&aProtocol);
    socketReader socketReader (&connectionHandler, &aProtocol);

    std::thread keyboardThread(std::ref(keyboardReader));
    std::thread socketThread(std::ref(socketReader));

    keyboardThread.join();
    socketThread.join();
}