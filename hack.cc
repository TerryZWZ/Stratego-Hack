#include "hack.h"

Hack::Hack(int id, int playerID, Board* board, Player* player):
    Ability(id, playerID, "Hack", board, player) {}

void Hack::ability(vector<shared_ptr<Link>> links, istream& in) {
    int r, c;

    cout << "Which firewall do you want removed? (Enter coordinates): ";

    while (true) {
        if (in >> r >> c && r < board->getSize() && c < board->getSize() && r >= 0 && c >= 0) {
            shared_ptr<Cell> cell = board->getGrid()[r][c];
            shared_ptr<Tile> tile = dynamic_pointer_cast<Tile>(cell);
            shared_ptr<Cell> newTile = make_shared<Tile>();

            if (cell->getChar() != newTile->getChar() && tile && !tile->occupied()) {
                board->setCell(r, c, newTile);
                break;
            }
            else {
                cout << "You have failed to hack in time..." << endl;
                break;
            }
        }
        else {
            cout << "Invalid input, please pick an actual firewall (Enter coordinates): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    abilityUsed();
    cout << getName() << " has been used!" << endl;
}
