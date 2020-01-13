//
// Created by lavih@wincs.cs.bgu.ac.il on 13/01/2020.
//

#include "socketReader.h"
#include <string>
#include <protocol.h>
#include <connectionHandler.h>

using namespace std;
void socketReader::readFromSocket() {
    string line;
    while(1){
        if (connectionHandler_.getLine(line)) {
            protocol_.proccesServerLine(line);
        }
    }

}
