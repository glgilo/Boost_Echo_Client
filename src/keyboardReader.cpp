//
// Created by igale@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include <iostream>
#include <sstream>
#include "keyboardReader.h"
using namespace std;

void keyboardReader::readFromKeyboard() {
    string line;
    while(1) {
        cin >> line;
        toFrame.clear();
        stringstream start(line);
        string tempWord;
        while (getline(start, tempWord, ' ')) {
            toFrame.push_back(tempWord);
        }
        protocol_.process(toFrame);
    }

}