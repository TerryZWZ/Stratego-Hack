#include "polarize.h"
#include "player.h"

using namespace std;

Polarize::Polarize(int id, int playerID, Board* board, Player* player) : Ability(id, playerID, "Polarize", board, player) {}

void Polarize::ability(vector<shared_ptr<Link>> links, istream& in) {
    vector<shared_ptr<Link>> opponentLinks = player->getOpponentLinks();
    char c; // link to polarize
    bool found = false;
    cout << "Link to polarize: ";
    while (in >> c) {
        // can polarize either your own or opponent links
        // current player links
        for (auto &link : links) {
            if (link->getChar() == c && !(link->getDownloaded())) {
                link->polarize();
                found = true;
            }
        }
        // opponent links
        for (auto &opponentLink : opponentLinks) {
            if (opponentLink->getChar() == c && !(opponentLink->getDownloaded())) {
                opponentLink->polarize();
                found = true;
            }
        }
        if (found) {
            break;
        }
        cout << "Cannot polarize " << c << ", please enter a valid link to polarize: ";
    }
    abilityUsed(); // set ability to used
    cout << getName() << " has been used!" << endl;
}
