//
// Created by igale@wincs.cs.bgu.ac.il on 12/01/2020.
//

#include <iostream>
#include <sstream>
#include "keyboardReader.h"
using namespace std;

keyboardReader::keyboardReader(protocol *Protocol) {
    protocol_= Protocol;
}

 void keyboardReader::operator()(){
    string line;
    while(1) {
        const short bufsize = 1024;
        char buf[bufsize];
        cout << "before cin" << endl;
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        toFrame.clear();
        stringstream start(line);
        string tempWord;
        while (getline(start, tempWord, ' ')) {
            toFrame.push_back(tempWord);
        }
        protocol_->process(toFrame);
    }

}