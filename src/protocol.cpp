//
// Created by igale@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include "protocol.h"
#include <string>
#include <vector>
#include <unordered_map>

void protocol::process(vector<string> frameToBuild) {
    string command = frameToBuild.at(0);
    string toSend;
    if(command == "join"){
        toSend = "SUBSCRIBE \n"
                        "destination:" + frameToBuild.at(1) + "\n "
                        "id:" + to_string(clientDB.getSubCount()) + "\n "
                        "receipt:" + to_string(clientDB.getReceiptCount()) + "\n";
        clientDB.getRequestWithReceipt().insert(make_pair(clientDB.getReceiptCount(),make_pair("SUBSCRIBE",frameToBuild.at(1))));
        clientDB.increaseSubId();
        clientDB.increaseReceipt();

    }
    else if(command == "exit"){
        toSend = "UNSUBSCRIBE \n"
                        "id:" + to_string(clientDB.getSubCount()) + "\n "
                        "receipt:" + to_string(clientDB.getReceiptCount()) + "\n";
        clientDB.getRequestWithReceipt().insert(make_pair(clientDB.getReceiptCount(),make_pair("UNSUBSCRIBE",frameToBuild.at(1))));
        clientDB.increaseReceipt();
}
    else if (command == "add"){
        toSend = "SEND \n"
                        "destination:" + frameToBuild.at(1) + "\n " +
                        clientDB.getUsername() + " has added the book " + frameToBuild.at(2) + "\n ";
        clientDB.addToMyBooks(frameToBuild.at(1),frameToBuild.at(2));
    }
    else if (command == "borrow"){
        toSend = "SEND \n"
                        "destination:" + frameToBuild.at(1) + "\n " +
                        clientDB.getUsername() + " wish to borrow " + frameToBuild.at(2) + "\n ";
    }
    else if (command == "return"){
        toSend = "SEND \n"
                        "destination:" + frameToBuild.at(1) + "\n " +
                        "returning " + frameToBuild.at(2) + " to" + clientDB.getBorrowedBooks().at(frameToBuild.at(2)) + "\n ";
        clientDB.removeFromMyBooks(frameToBuild.at(1), frameToBuild.at(2));
        clientDB.getBorrowedBooks().erase(frameToBuild.at(2));
    }
    else if (command == "status"){
        toSend = "SEND \n"
                 "destination:" + frameToBuild.at(1) + "\n " +
                 "Bok status \n";
    }
    else if (command == "logout") {
        toSend = "DISCONNECT \n"
                 "receipt:" + to_string(clientDB.getReceiptCount()) + "\n ";
        clientDB.getRequestWithReceipt().insert(make_pair(clientDB.getReceiptCount(),make_pair("DISCONNECT",nullptr)));
        clientDB.increaseReceipt();
    }
    connectionHandler_.sendLine(toSend);
}