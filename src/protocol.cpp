//
// Created by igale@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include "protocol.h"
#include <string>
#include <vector>
#include <unordered_map>


protocol::protocol(ConnectionHandler *connectionHandler) {
    connectionHandler_ = connectionHandler;
}

void protocol::process(vector<string> frameToBuild) {
    string command = frameToBuild.at(0);
    string toSend;
    if(command == "join"){
        toSend = "SUBSCRIBE\n"
                        "destination:" + frameToBuild.at(1) + "\n"
                        "id:" + to_string(clientDB.getSubCount()) + "\n"
                        "receipt:" + to_string(clientDB.getReceiptCount()) + "\n";
        clientDB.getRequestWithReceipt().insert(make_pair(clientDB.getReceiptCount(),make_pair("SUBSCRIBE",frameToBuild.at(1))));
        clientDB.getWantToSubscribe().insert(make_pair(frameToBuild.at(1),clientDB.getSubCount()));
        clientDB.increaseSubId();
        clientDB.increaseReceipt();

    }
    else if(command == "exit"){
        toSend = "UNSUBSCRIBE\n"
                        "id:" + to_string(clientDB.getSubscribedTo().at(frameToBuild.at(1))) + "\n"
                        "receipt:" + to_string(clientDB.getReceiptCount()) + "\n";
        clientDB.getRequestWithReceipt().insert(make_pair(clientDB.getReceiptCount(),make_pair("UNSUBSCRIBE",frameToBuild.at(1))));
        clientDB.increaseReceipt();
}
    else if (command == "add"){
        string book = bookRemoveSpace(frameToBuild);
        toSend = "SEND\n"
                        "destination:" + frameToBuild.at(1) + "\n\n" +
                        clientDB.getUsername() + " has added the book " + book + "\n";
        clientDB.addToMyBooks(frameToBuild.at(1),book);
    }
    else if (command == "borrow"){
        string book = bookRemoveSpace(frameToBuild);
        toSend = "SEND\n"
                        "destination:" + frameToBuild.at(1) + "\n\n" +
                        clientDB.getUsername() + " wish to borrow " + book + "\n";
        clientDB.getWishToBorrow().push_back(book);

    }
    else if (command == "return"){
        toSend = "SEND\n"
                        "destination:" + frameToBuild.at(1) + "\n\n" +
                        "Returning " + bookRemoveSpace(frameToBuild) + " to " + clientDB.getBorrowedBooks().at(frameToBuild.at(2)) + "\n";
        clientDB.removeFromMyBooks(frameToBuild.at(2), frameToBuild.at(1));
        clientDB.getBorrowedBooks().erase(frameToBuild.at(2));
    }
    else if (command == "status"){
        toSend = "SEND\n"
                 "destination:" + frameToBuild.at(1) + "\n\n" +
                 "Book status\n";
    }
    else if (command == "logout") {
        toSend = "DISCONNECT\n"
                 "receipt:" + to_string(clientDB.getReceiptCount()) + "\n";
        clientDB.getRequestWithReceipt().insert(make_pair(clientDB.getReceiptCount(),make_pair("DISCONNECT","")));
        clientDB.increaseReceipt();
    }
    cout << toSend << endl; //////////////////////////////delete later
    connectionHandler_->sendLine(toSend);
}

void protocol::proccesServerLine(vector<string> fromFrame) {
    cout << "reading line from socket" <<endl; ///////////////////////////delete later
    string type = fromFrame.at(0);
    if(type == "CONNECTED") {
        cout << "Login successful" << endl;
    }
    else if (type == "ERROR") {
        cout <<fromFrame.at(0) + "\n" + fromFrame.at(1) <<endl;
        socketTermination = true;
        connectionHandler_->close();
        cout << "The connection was closed because of ERROR" << endl;
    }
    else if(type == "RECEIPT"){
        string id = splitAndGetSecondWord(fromFrame.at(1),':');
        pair<string,string> handleProperly = clientDB.getRequestWithReceipt().at(stoi(id));
        if(handleProperly.first == "SUBSCRIBE"){
            clientDB.getSubscribedTo().insert(make_pair(handleProperly.second,clientDB.getWantToSubscribe().at(handleProperly.second)));
            clientDB.getWantToSubscribe().erase(handleProperly.second);
            cout << "Joined club " + handleProperly.second << endl;
        }
        else if(handleProperly.first == "UNSUBSCRIBE"){
            clientDB.getSubscribedTo().erase(handleProperly.second);
            cout << "Exited club " + handleProperly.second << endl;
        }
        else if(handleProperly.first == "DISCONNECT"){
            //////Amit added this//////
//            for (pair<string,int> topic : clientDB.getSubscribedTo()){
//                string toSend = "UNSUBSCRIBE\n"
//                         "id:" + to_string(topic.second) + "\n"
//                                                           "receipt:" + to_string(clientDB.getReceiptCount()) + "\n";
//                clientDB.getRequestWithReceipt().insert(make_pair(clientDB.getReceiptCount(),make_pair("UNSUBSCRIBE",topic.first)));
//                clientDB.increaseReceipt();
//                connectionHandler_->sendLine(toSend);
//            }
            /////////////////////////
            socketTermination = true;
            connectionHandler_->close();
            cout << clientDB.getUsername() + " has logged out successfully" << endl;
        }
        clientDB.getRequestWithReceipt().erase(stoi(id));
    }
    else if(type == "MESSAGE"){
        string subType = discoverType(fromFrame.at(4));
        if(subType == "add") {
            vector <string> frame = stringToVector(fromFrame.at(4), ' ');
            string book = bookAddSpace(frame.at(5));
            for (int i = 0;(unsigned) i < frame.size()-1; i++)
                cout << frame.at(i) + " ";
            cout << book << endl;
        }
        if(subType == "borrow"){
            vector<string> check = stringToVector(fromFrame.at(4), ' ');
            string bookToBorrow = stringToVector(fromFrame.at(4),' ').at(4);
            vector <string> frame = stringToVector(fromFrame.at(4), ' ');
            string book = bookAddSpace(frame.at(4));
            for (int i = 0;(unsigned) i < frame.size()-1; i++)
                cout << frame.at(i) + " ";
            cout << book << endl;
            string destination = splitAndGetSecondWord(fromFrame.at(3),':');
            if (clientDB.getMyBooks().count(destination) > 0 && contains(clientDB.getMyBooks().at(destination),bookToBorrow)){
                string toSend = "SEND\n"
                                "destination:" + destination + "\n\n" +
                                clientDB.getUsername() + " has " + bookToBorrow + "\n";
                connectionHandler_->sendLine(toSend);
//                clientDB.removeFromMyBooks(bookToBorrow,destination);
//                if (clientDB.getBorrowedBooks().count(bookToBorrow) != 0)
//                    clientDB.getBorrowedBooks().erase(bookToBorrow);
            }
        }
        if(subType == "checkIfIWant"){
            vector <string> frame = stringToVector(fromFrame.at(4), ' ');
            string owner = stringToVector(fromFrame.at(4), ' ').at(0);
            string book = stringToVector(fromFrame.at(4), ' ').at(2);
            string bookRepaired = bookAddSpace(book);
            for (int i = 0;(unsigned) i < frame.size()-1; i++)
                cout << frame.at(i) + " ";
            cout << bookRepaired << endl;
            string destination = splitAndGetSecondWord(fromFrame.at(3),':');
            if(contains(clientDB.getWishToBorrow(),book)){
                string toSend = "SEND\n"
                             "destination:" + destination + "\n\n" +
                              "Taking " + book + " from " + owner + "\n";
                connectionHandler_->sendLine(toSend);
                clientDB.addToMyBooks(destination, book);
                clientDB.removeFromWishToBorrow(book);
                clientDB.getBorrowedBooks().insert(make_pair(book,owner));
                cout << "Taking " + book + " from " + owner << endl;
            }
        }
        if(subType == "status"){
            string destination = splitAndGetSecondWord(fromFrame.at(3),':');
            cout << fromFrame.at(4) << endl;
            if(clientDB.getMyBooks().count(destination) != 0 && !clientDB.getMyBooks().at(destination).empty()) {//////////////////////TODO:igal added
                string check = myBooksByTopic(destination);
                string toSend = "SEND\n"
                                "destination:" + destination + "\n\n" +
                                clientDB.getUsername() + ":" + myBooksByTopic(destination)+ "\n";
                connectionHandler_->sendLine(toSend);
            }
        }
        if (subType == "returning"){
            vector <string> frame = stringToVector(fromFrame.at(4), ' ');
            string name = stringToVector(fromFrame.at(4), ' ').at(3);
            string book = stringToVector(fromFrame.at(4), ' ').at(1);
            string bookRepaired = bookAddSpace(book);
            cout << "Returning " + bookRepaired + " to " + name << endl;
            string destination = splitAndGetSecondWord(fromFrame.at(3),':');
            if (clientDB.getUsername() == name)
                clientDB.addToMyBooks(destination, book);

        }
        if(subType == "books"){
            string owner = splitAndGetFirstWord(fromFrame.at(4), ':');
            string booksWithComma = splitAndGetSecondWord(fromFrame.at(4), ':');
            vector<string> books = stringToVector(booksWithComma, ',');
            string toPrint = owner + ":";
            for (string book : books){
                toPrint = toPrint + bookAddSpace(book) + ",";
            }
            cout << toPrint.substr(0,toPrint.size() - 1) << endl;
        }
        if(subType == "Taking"){
            vector<string> body = stringToVector(fromFrame.at(4),' ');
            string bookName = bookAddSpace(body.at(1));
            string destination = splitAndGetSecondWord(fromFrame.at(3),':');
            string owner = body.at(3);
            if(clientDB.getUsername() == owner) {
                clientDB.removeFromMyBooks(body.at(1), destination);
//                if (clientDB.getBorrowedBooks().count(bookName) != 0)
//                    clientDB.getBorrowedBooks().erase(bookName);
            }
            cout << body.at(0) + " " + bookName + " " + body.at(2) + " " + body.at(3) << endl;
        }
    }
}

string protocol::splitAndGetSecondWord(string word, char delimiter) {
    std::size_t pos = word.find(delimiter);
    return word.substr(pos + 1);
}

string protocol::splitAndGetFirstWord(string word, char delimiter) {
    std::size_t pos = word.find(delimiter);
    return word.substr(0,pos );
}

string protocol::discoverType(string body){
    string toReturn;
    vector<string> words;
    stringstream start(body);
    string tempWord;
    while (getline(start, tempWord, ' ')) {
        words.push_back(tempWord);
    }
    if(words.size() > 2 && words.at(2) == "added")
        return "add";
    if(words.size() > 3 && words.at(3) == "borrow")
        return "borrow";
    if(words.size() == 3 && words.at(1) == "has")
        return "checkIfIWant";
    if(words.size() > 1 && words.at(1) == "status")
        return "status";
    if(!words.empty() && words.at(0) == "Returning")
        return "returning";
    //////Amit added this////////
    if(!words.empty() && words.at(0) == "Taking")
        return "Taking";
    ////////////////////////////
    return "books";
}

bool protocol::contains(vector<string> &wishBooks, string &bookToBorrow) {
    for(string &book : wishBooks)
        if (book == bookToBorrow)
            return true;
    return false;

}

vector<string> protocol::stringToVector (string &s, char delimiter) {
    vector<string> toReturn;
    stringstream start(s);
    string tempWord;
    while (getline(start, tempWord, delimiter)) {
        toReturn.push_back(tempWord);
    }
    return toReturn;
}

string protocol::myBooksByTopic(string& topic){
    string s;
    vector<string> byTopic = clientDB.getMyBooks().at(topic);
    for (string book : byTopic)
        s = s + book + ",";
    return s.substr(0,s.size() - 1); //todo: check size -1
}

bool protocol::isSocketTermination() const {
    return socketTermination;
}

clientDataBase &protocol::getClientDb() {
    return clientDB;
}

string protocol::bookRemoveSpace(vector<string> toRepair){
    string repaired;
    for(int i = 2;(unsigned) i<toRepair.size();i++){
        repaired = repaired + toRepair.at(i) + '-';
    }
    return repaired.substr(0,repaired.size()-1);
}

string protocol::bookAddSpace(string toRepair){
    string repaired;
    for (char c : toRepair) {
        if (c == '-')
            repaired = repaired + " ";
        else
            repaired = repaired + c;
    }
    return repaired;
}

