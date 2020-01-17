//
// Created by igale@wincs.cs.bgu.ac.il on 12/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_KEYBOARDREADER_H
#define BOOST_ECHO_CLIENT_KEYBOARDREADER_H



using namespace std;

class keyboardReader {
private:
    vector<string> toFrame;
    protocol* protocol_;

public:
    ~keyboardReader()= default;
    keyboardReader(const keyboardReader&)= default;
    keyboardReader &operator=(const keyboardReader&)= default;
    keyboardReader(protocol*);

    void operator()();
};


#endif //BOOST_ECHO_CLIENT_KEYBOARDREADER_H
