#include "textdisplay.h"

TextDisplay::TextDisplay(int n): boardSize{n} {
    vector<char> row;
    // empty 8x8 board
    for (int i = 0; i < boardSize; ++i) {
        row.emplace_back('.');
    }
    for (int i = 0 ; i < boardSize; ++i) {
        display.emplace_back(row);
    }
}

void TextDisplay::notify(Cell &c) {
    int row = c.getRow();
    int col = c.getCol();

    if (c.getState()) {
        display[row][col] = c.getChar();
    }
}

void TextDisplay::notifyInfo(int abilityCount, int data, int viruses, vector<shared_ptr<Link>> links, int playerID) {
    if (playerID == 1) {
        p1.playerID = playerID;
        p1.abilityCount = abilityCount;
        p1.data = data;
        p1.viruses = viruses;
        p1.links = links;
    }
    else if (playerID == 2) {
        p2.playerID = playerID;
        p2.abilityCount = abilityCount;
        p2.data = data;
        p2.viruses = viruses;
        p2.links = links;
    }
}

TextDisplay::~TextDisplay() {}

void TextDisplay::setPlayerTurn(int turn) {
    playerTurn = turn;
}

string TextDisplay::getLinkInfo(shared_ptr<Link> link) const {
    // if link is hidden and it's not its owner's turn
    if (link->getHidden() && link->getPlayerID() != playerTurn) {
        return "? ";
    }
    else if (link->getIsData()) {
        return "D" + to_string(link->getStrength());
    }
    else {
        return "V" + to_string(link->getStrength());
    }
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
    out << "Player 1:" << endl;
    out << "Downloaded: " << td.p1.data << "D, " << td.p1.viruses << "V" << endl;
    out << "Abilities: " << td.p1.abilityCount << endl;
    // link info for player 1
    for (int i = 0; i < td.boardSize; ++i) {
        if (i == 4) {
            out << endl;
        }
        out << td.p1.links.at(i)->getChar() << ": " << td.getLinkInfo(td.p1.links.at(i)) << " ";
    }
    out << endl;
    out << "========" << endl;
    // row
    for (int i = 0; i < td.boardSize; ++i) {
        // col
        for (int j = 0; j < td.boardSize; ++j) {
            out << td.display[i][j];
        }
        out << endl;
    }
    out << "========" << endl;
    out << "Player 2:" << endl;
    out << "Downloaded: " << td.p2.data << "D, " << td.p2.viruses << "V" << endl;
    out << "Abilities: " << td.p2.abilityCount << endl;
    // link info for player 2
    for (int i = 0; i < td.boardSize; ++i) {
        if (i == 4) {
            out << endl;
        }
        out << td.p2.links.at(i)->getChar() << ": " << td.getLinkInfo(td.p2.links.at(i)) << " ";
    }
    out << endl;
    return out;
}
