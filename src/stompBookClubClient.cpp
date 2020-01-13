//
// Created by igale@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include "stompBookClubClient.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;


int main() {
    vector<string> temp;
    do {
        temp.clear();
        string line;
        cin >> line;
        stringstream start(line);
        string tempWord;
        while (getline(start, tempWord, ' ')) {
            temp.push_back(tempWord);
        }
    }
    while(temp.at(0) != "login");
}