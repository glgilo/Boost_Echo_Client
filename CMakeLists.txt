cmake_minimum_required(VERSION 3.15)
project(Boost_Echo_Client)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Boost_Echo_Client
        include/connectionHandler.h
        include/stompBookClubClient.h
        include/keyboardReader.h
        include/protocol.h
        include/clientDataBase.h
        include/socketReader.h
        src/socketReader.cpp
        src/connectionHandler.cpp
        src/echoClient.cpp
        src/stompBookClubClient.cpp
        src/keyboardReader.cpp
        src/protocol.cpp
        src/clientDataBase.cpp
        makefile)
