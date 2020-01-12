//
// Created by igale@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_KEYBOARDREADER_H
#define BOOST_ECHO_CLIENT_KEYBOARDREADER_H

#include <string>
#include <vector>
#include "protocol.h"

using namespace std;

class keyboardReader {
private:
    vector<string> toFrame;
    protocol protocol_;

public:
    void readFromKeyboard();
};


#endif //BOOST_ECHO_CLIENT_KEYBOARDREADER_H
