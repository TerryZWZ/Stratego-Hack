#include "download.h"
#include "player.h"

using namespace std;

Download::Download(int id, int playerID, Board* board, Player* player) : Ability(id, playerID, "Download", board, player) {}

void Download::ability(vector<shared_ptr<Link>> links, istream& in) {
    vector<shared_ptr<Link>> oppoLinks = player->getOpponentLinks();
    char ch;
    bool existence = false;
    cout << "Link to download: ";
    while (in >> ch) {
        // can only download opponent links
        for (auto &oppoLink : oppoLinks ) {
            // if match, not downloaded and not encrypted
            if (oppoLink->getChar() == ch && !(oppoLink->getDownloaded()) && !(oppoLink->getIsEncrypted())) {
                player->download(*oppoLink);
                static_cast<Tile*>(board->getCell(oppoLink->getX(), oppoLink->getY()))->removeLink();
                board->getCell(oppoLink->getX(), oppoLink->getY())->notifyObservers();
                existence = true;
            }
        }
        if (existence) {
            break;
        }
        cout << "Cannot download " << ch << ", please enter a valid link to download: ";
    }
    abilityUsed();
    cout << getName() << " has been used!" << endl;
}
