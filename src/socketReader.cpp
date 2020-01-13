//
// Created by lavih@wincs.cs.bgu.ac.il on 13/01/2020.
//

#include "socketReader.h"
#include <string>
#include <iostream>
#include <protocol.h>
#include <connectionHandler.h>

using namespace std;
void socketReader::readFromSocket() {
    while(1){
        string line;
        if (connectionHandler_.getLine(line)) {
            fromFrame.clear();
            stringstream start(line);
            string tempWord;
            while (getline(start, tempWord, '\n')) {
                fromFrame.push_back(tempWord);
            }
            protocol_.proccesServerLine(fromFrame);
        }
    }

}
