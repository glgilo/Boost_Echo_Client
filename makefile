CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system

all: StompClient
StompClient: bin/connectionHandler.o bin/clientDataBase.o bin/keyboardReader.o bin/protocol.o bin/socketReader.o bin/stompBookClubClient.o

	@echo 'Building target: Stomp Client'
	@echo 'Invoking: c++ Linker'

	g++ -pthread -o bin/connectionHandler.o bin/clientDataBase.o bin/keyboardReader.o bin/protocol.o bin/socketReader.o bin/stompBookClubClient.o $(LDFLAGS)

	@echo 'Finished building target: Stomp Client'
	@echo ' '

bin/keyboardReader.o: src/keyboardReader.cpp
	g++ $(CFLAGS) -o bin/keyboardReader.o src/keyboardReader.cpp

bin/connectionHandler.o: src/connectionHandler.cpp
	g++ $(CFLAGS) -o bin/connectionHandler.o src/connectionHandler.cpp

bin/clientDataBase.o: src/clientDataBase.cpp
	g++ $(CFLAGS) -o bin/clientDataBase.o src/clientDataBase.cpp

bin/protocol.o: src/protocol.cpp
	g++ $(CFLAGS) -o bin/protocol.o src/protocol.cpp

bin/socketReader.o: src/socketReader.cpp
	g++ $(CFLAGS) -o bin/socketReader.o src/socketReader.cpp

bin/stompBookClubClient.o: src/stompBookClubClient.cpp
	g++ $(CFLAGS) -o bin/stompBookClubClient.o src/stompBookClubClient.cpp


.PHONY: clean
clean:
	rm -f bin/*
