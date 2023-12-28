#include "encrypt.h"

Encrypt::Encrypt(int id, int playerID, Board* board, Player* player) : Ability(id, playerID, "Encrypt", board, player) {}

void Encrypt::ability(vector<shared_ptr<Link>> links, istream& in) {
    bool found = false;
    char c;
    cout << "Link to encrypt: ";
    while (in >> c) {
        // can only encrypt own links
        for (auto &link : links) {
            // link NOT encrypted and NOT downloaded
            if (link->getChar() == c && !(link->getIsEncrypted()) && !(link->getDownloaded())) {
                link->encrypt();
                found = true;
            }
        }
        if (found) {
            break;
        }
        cout << "Cannot encrypt " << c << ", please enter a valid link to encrypt: ";
    }
    abilityUsed();
    cout << getName() << " has been used!" << endl;
}
