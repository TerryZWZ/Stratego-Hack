#include "server.h"

Server::Server(int playerID) : Cell{true, true}, playerID{playerID} {}

int Server::getPlayer(){
    return playerID;
}

char Server::getChar() const {
    return 'S';
}
