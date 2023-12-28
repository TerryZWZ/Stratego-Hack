#include "firewall.h"
#include "player.h"

using namespace std;

Firewall::Firewall(int id, int playerID, Board* board, Player* player) : Ability(id, playerID, "Firewall", board, player) {}

void Firewall::ability(vector<shared_ptr<Link>> links, istream& in) {
    int r, c;

    cout << "Which tile do you want to place the firewall on (Enter coordinates): ";

    while (true) {
        if (in >> r >> c && r < board->getSize() && c < board->getSize() && r >= 0 && c >= 0) {
            shared_ptr<Cell> cell = board->getGrid()[r][c];
            shared_ptr<Tile> tile = dynamic_pointer_cast<Tile>(cell);
            shared_ptr<FirewallTile> firewallTile = make_shared<FirewallTile>(tile, playerID, player);
            shared_ptr<Tile> sampleTile = make_shared<Tile>();

            if (cell->getChar() == sampleTile->getChar() && tile && !tile->occupied()) {
                board->setCell(r, c, firewallTile);
                break;
            }
            else {
                cout << "That tile is not empty, pick another tile (Enter coordinates): ";
            }
        }
        else {
            cout << "Invalid input, please pick an actual tile (Enter coordinates): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    abilityUsed();
    cout << getName() << " has been used!" << endl;
}
