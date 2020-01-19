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
//    while (1) {
        do {
            cout << "please login" << endl;
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
            if(temp.at(0) == "bye")
                break;
        } while (temp.at(0) != "login");
//        if(temp.at(0) == "bye")
//            break;
        string toSend = "CONNECT\n"
                        "accept-version:1.2\n"
                        "host:stomp.cs.bgu.ac.il\n"
                        "login:" + temp.at(2) + "\n"
                                                "passcode:" + temp.at(3) + "\n\n";
        int delimiter = temp.at(1).find(':') + 1;
        short port = (short) stoi(temp.at(1).substr(delimiter));
        string host = temp.at(1).substr(0, delimiter - 1);
        ConnectionHandler connectionHandler(host, port);
        protocol aProtocol(&connectionHandler);
        aProtocol.getClientDb().setUsername(temp.at(2));
        connectionHandler.connect();
        connectionHandler.sendLine(toSend);

        keyboardReader keyboardReader(&aProtocol);
        socketReader socketReader(&connectionHandler, &aProtocol);

        std::thread keyboardThread(std::ref(keyboardReader));
        std::thread socketThread(std::ref(socketReader));

        keyboardThread.join();
        socketThread.join();
    }
//}