//
// Created by igale@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include "clientDataBase.h"
#include <unordered_map>
using namespace std;

const string &clientDataBase::getUsername() const {
    return username;
}

unordered_map<string, vector<string>> &clientDataBase::getMyBooks() {
    return myBooks;
}

unordered_map<string, string> &clientDataBase::getBorrowedBooks()  {
    return borrowedBooks;
}

unordered_map<int, pair<string,string>> &clientDataBase::getRequestWithReceipt() {
    return requestWithReceipt;
}

int clientDataBase::getReceiptCount() const {
    return receiptCount;
}

 unordered_map<string, int> &clientDataBase::getSubscribedTo()  {
    return subscribedTo;
}

int clientDataBase::getSubCount() const {
    return subCount;
}

void clientDataBase::increaseReceipt() {
    receiptCount++;
}

void clientDataBase::increaseSubId() {
    subCount++;
}

void clientDataBase::addToMyBooks (string topic, string book) {
    if (myBooks.count(topic) != 0)
        myBooks.at(topic).push_back(book);
    else {
        vector<string> books;
        myBooks.insert(make_pair(topic, books));
        myBooks.at(topic).push_back(book);
    }
}

void clientDataBase::removeFromMyBooks(string book, string topic) {
    for(int i = 0;i< myBooks.at(topic).size();i++){
        if(book ==  myBooks.at(topic).at(i))
            myBooks.at(topic).erase( myBooks.at(topic).begin() +i);
    }

}

 unordered_map<string,int> &clientDataBase::getWantToSubscribe()  {
    return wantToSubscribe;
}

 vector<string> &clientDataBase::getWishToBorrow()  {
    return wishToBorrow;
}
