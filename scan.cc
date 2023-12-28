#include "scan.h"
#include "player.h"

using namespace std;

Scan::Scan(int id, int playerID,  Board* board, Player* player) : Ability(id, playerID, "Scan", board, player) {}

void Scan::ability(vector<shared_ptr<Link>> links, istream& in) {
    vector<shared_ptr<Link>> opponentLinks = player->getOpponentLinks();
    bool valid = false;
    char c; // link to scan
    cout << "Link to scan: ";
    while (in >> c) {
        // can scan either your own or opponent links
        // find the corresponding link and reveal it if hidden
        // scanning your own link does nothing
        for (auto &link : links) {
            // match, hidden, not encrypted, not downloaded
            if (link->getChar() == c && link->getHidden() && !(link->getIsEncrypted()) && !(link->getDownloaded())) {
                //link->reveal();
                //board->getGrid()[link->getX()][link->getY()]->notifyObservers();
                valid = true;
            }
        }
        for (auto &opponentLink : opponentLinks) {
            // match, hidden, not encrypted, not downloaded
            if (opponentLink->getChar() == c && opponentLink->getHidden() && 
                !(opponentLink->getIsEncrypted()) && !(opponentLink->getDownloaded())) {
                opponentLink->reveal();
                board->getGrid()[opponentLink->getX()][opponentLink->getY()]->notifyObservers();
                valid = true;
            }
        }
        if (valid) {
            break;
        }
        cout << "Cannot scan " << c << ", please enter a valid link to scan: ";
    }
    abilityUsed();
    cout << getName() << " has been used!" << endl;
}
