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
    unordered_map<string, vector<string>> myBooks;// <topic,books>
    unordered_map<string, string> borrowedBooks; //<book,owner>
    vector<string> wishToBorrow;
    unordered_map<int,pair<string,string>> requestWithReceipt;//<receipt id,<type,genre>>
    int receiptCount = 1;
    unordered_map<string,int> subscribedTo;//<subId,genre>//hafuh
    unordered_map<string,int> wantToSubscribe;
    int subCount = 1;
public:
    clientDataBase();

    void increaseReceipt();

    void increaseSubId();

    void addReceipt(int,string);

    unordered_map<string, vector<string>> &getMyBooks() ;

    unordered_map<string, string> &getBorrowedBooks();

     vector<string> &getWishToBorrow();

    unordered_map<int, pair<string,string>> &getRequestWithReceipt();

    int getReceiptCount() const;

     unordered_map<string, int> &getSubscribedTo() ;

    int getSubCount() const;

    const string &getUsername() const;

    void setUsername(const string &username);

    void addToMyBooks (string, string);

    void removeFromMyBooks(string&, string&);

     unordered_map<string,int> &getWantToSubscribe() ;

     void removeFromWishToBorrow(string&);

};



#endif //BOOST_ECHO_CLIENT_CLIENTDATABASE_H
