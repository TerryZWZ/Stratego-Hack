#include "game.h"

using namespace std;

enum class Colour {
    BLACK = 30,
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    CYAN = 36,
    WHITE = 37,
    BRIGHT_RED = 91,
    BRIGHT_GREEN = 92,
    BRIGHT_YELLOW = 93,
    BRIGHT_BLUE = 94,
    BRIGHT_MAGENTA = 95,
    BRIGHT_CYAN = 96,
    BRIGHT_WHITE = 97
};

string colour(Colour colour) {
    return "\033[" + to_string(static_cast<int>(colour)) + "m";
}

Game::Game(bool graphics): graphics{graphics}, p1{1, &board}, p2{2, &board} {
    p1.setOpponent(&p2);
    p2.setOpponent(&p1);

    shared_ptr<TextDisplay> td = make_shared<TextDisplay>(board.getSize());
    if (graphics) {
        shared_ptr<GraphicsDisplay> gd = make_shared<GraphicsDisplay>(board.getSize());
        board.init(td, gd);
        p1.attach(gd);
        p2.attach(gd);
    }
    else {
        board.init(td, nullptr);
    }
    p1.attach(td);
    p2.attach(td);

    cout << colour(Colour::BLUE) << "Welcome to RAIINet!" << colour(Colour::WHITE) << endl;
}
Player &Game::getPlayer(int playerID) { 
    return (playerID == 1 ? p1 : p2); 
}

void Game::addAbility(const string& player, const string& abilities) {
    cout << colour(Colour::BRIGHT_RED);
    if (player == "p1") {
        cout << "Player 1:" << endl;

        int i = 1;
        for (char ability : abilities) {
            p1.addAbility(ability, i);
            i++;
        }
    }
    else if (player == "p2") {
        cout << "Player 2:" << endl;

        int i = 1;
        for (char ability : abilities) {
            p2.addAbility(ability, i);
            i++;
        }
    }
    cout << colour(Colour::WHITE) << endl;
}

void Game::abilityList(int player) {
    if (player == 1) {
        cout << "Player 1 Abilities:" << endl;
        p1.abilityList();
    }
    else if (player == 2) {
        cout << "Player 2 Abilities:" << endl;
        p2.abilityList();
    }
}

void Game::addLinks(int playerNum, istream& in){
    for (int i = 0 ; i < 8; ++i){
        char type;
        int strength;
        in >> type >> strength;
        getPlayer(playerNum).addLink(type, strength, i);
    }
}

Winner Game::checkWin() {
    if (p1.dataCount() == winCondition || p2.virusCount() == winCondition) {
        return {true, 1};
    }
    else if (p2.dataCount() == winCondition || p1.virusCount() == winCondition) {
        return {true, 2};
    }
    return {false, 0};
}

void Game::runGame(){
    playerTurn = 1;
    string cmd;
    int abilitiesUsed = 0;
    bool success; // for indicating using ability success

    board.getTextDisplay()->setPlayerTurn(playerTurn); // update player turn for text display
    if (graphics) { // update turn for graphics
        board.getGraphicsDisplay()->setPlayerTurn(playerTurn);
    }
    p1.notifyObservers();
    p2.notifyObservers();
    board.update();
    cout << board << endl;

    while (true) {
        if (checkWin().win) {
            cout << "Player " << checkWin().playerID << " has won the game!" << endl;
            break;
        }

        cout << colour(Colour::BRIGHT_GREEN) << "Player " << playerTurn << "'s Turn:" << colour(Colour::WHITE) << endl;
        
        cin >> cmd;

        if (cin.eof()) {
            break;
        }
        else if (cmd == "move") {
            char linkID;
            string dir;
            cin >> linkID >> dir;
            Direction moveDir = toDirection(dir);
            if (getPlayer(playerTurn).getLink(linkID) == -1 || moveDir == Direction::Stand){
                cout << "Could not accept inputs to move command!" << endl;
                continue;
            }
            if (!getPlayer(playerTurn).moveLink(linkID, moveDir)){
                cout << "Invalid move!" << endl;
                continue;
            }
            playerTurn = (playerTurn == 1 ? 2 : 1); // update playerTurn
            board.getTextDisplay()->setPlayerTurn(playerTurn);
            if (graphics) {
                board.getGraphicsDisplay()->setPlayerTurn(playerTurn);
            }
            p1.notifyObservers();
            p2.notifyObservers();
            abilitiesUsed = 0; // reset after each move
            cout << board << endl;
        }
        else if (cmd == "abilities") {
            if (playerTurn == 1) {
                abilityList(1);
            }
            else if (playerTurn == 2) {
                abilityList(2);
            }
        }
        else if (cmd == "ability") {
            int id;
            cin >> id;

            if (abilitiesUsed == 1) {
                cout << "You have already used the max number of abilities for this turn." << endl;
            }
            else if (playerTurn == 1) {
                success = p1.useAbility(id, cin);
                
                p1.notifyObservers();
                p2.notifyObservers();
                if (success) {
                    ++abilitiesUsed;
                }
            }
            else if (playerTurn == 2) {
                success = p2.useAbility(id, cin);

                p1.notifyObservers();
                p2.notifyObservers();
                if (success) {
                    ++abilitiesUsed;
                }
            }
            else {
                cout << "That player doesn't exist" << endl;
            }
            cout << board << endl;
        }
        else if (cmd == "board") {
            cout << board << endl;
        }
        else if (cmd == "sequence") {
            string filename;

            cin >> filename;
            ifstream file{filename}; // open file to read

            if (file.is_open()) {
                string command;
                // read commands from file
                while (file >> command) {
                    if (command == "move") {
                        char linkID;
                        string dir;
                        file >> linkID >> dir;
                        Direction moveDir = toDirection(dir); // get direction
                        // invalid linkID or invalid direction
                        if (getPlayer(playerTurn).getLink(linkID) == -1 || moveDir == Direction::Stand){
                            cout << "Could not accept inputs to move command!" << endl;
                            continue;
                        }
                        if (!getPlayer(playerTurn).moveLink(linkID, moveDir)){
                            cout << "Invalid move!" << endl;
                            continue;
                        }
                        playerTurn = (playerTurn == 1 ? 2 : 1); // update playerTurn
                        board.getTextDisplay()->setPlayerTurn(playerTurn);
                        if (graphics) {
                            board.getGraphicsDisplay()->setPlayerTurn(playerTurn);
                        }
                        p1.notifyObservers();
                        p2.notifyObservers();
                        abilitiesUsed = 0;
                        cout << board << endl;
                    }
                    else if (command == "abilities") {
                        if (playerTurn == 1) {
                            abilityList(1);
                        }
                        else if (playerTurn == 2) {
                            abilityList(2);
                        }
                    }
                    else if (command == "ability") {
                        int abilityID;
                        file >> abilityID;

                        if (abilitiesUsed == 1) {
                            cout << "You have already used the max number of abilities for this turn." << endl;
                        }
                        else if (playerTurn == 1) {
                            success = p1.useAbility(abilityID, file);

                            p1.notifyObservers();
                            p2.notifyObservers();
                            if (success) {
                                ++abilitiesUsed;
                            }
                        }
                        else if (playerTurn == 2) {
                            success = p2.useAbility(abilityID, file);
                            
                            p1.notifyObservers();
                            p2.notifyObservers();
                            if (success) {
                                ++abilitiesUsed;
                            }
                        }
                        else {
                            cout << "That player doesn't exist" << endl;
                        }
                        cout << board << endl;
                    }
                    else if (command == "board") {
                        cout << board;
                    }
                    else if (command == "quit") {
                        break;
                    }
                }
            }
            file.close();
        }
        else if (cmd == "quit") {
            break;
        }
        else {
            cout << "Command not found!" << endl;
            cin.clear();
            cin.ignore();
        }
    }
}
