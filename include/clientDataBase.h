//
// Created by igale@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_CLIENTDATABASE_H
#define BOOST_ECHO_CLIENT_CLIENTDATABASE_H

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class clientDataBase {
private:
    string username;
    unordered_map<string, vector<string>> myBooks;
    unordered_map<string, string> borrowedBooks;
    unordered_map<int,pair<string,string>> requestWithReceipt;
    int receiptCount = 1;
    unordered_map<int,string> subscribedTo;
    int subCount = 1;
public:
    void increaseReceipt();

    void increaseSubId();

    void addReceipt(int,string);

    unordered_map<string, vector<string>> &getMyBooks() ;

    unordered_map<string, string> &getBorrowedBooks();

    unordered_map<int, pair<string,string>> &getRequestWithReceipt();

    int getReceiptCount() const;

    const unordered_map<int, string> &getSubscribedTo() const;

    int getSubCount() const;

    const string &getUsername() const;

    void addToMyBooks (string, string);

    void removeFromMyBooks(string, string);

};



#endif //BOOST_ECHO_CLIENT_CLIENTDATABASE_H
