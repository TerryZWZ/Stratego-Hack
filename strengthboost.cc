#include "strengthboost.h"

StrengthBoost::StrengthBoost(int id, int playerID, Board *board, Player *player):
    Ability(id, playerID, "Strength Boost", board, player) {}

void StrengthBoost::ability(vector<shared_ptr<Link>> links, istream& in) {
    bool boosted = false;
    char c;
    cout << "Link to strength boost: ";
    while (in >> c) {
        // can only strength boost own links
        for (auto &link : links) {
            // match and not downloaded
            if (link->getChar() == c && !(link->getDownloaded())) {
                link->strengthBoost();
                boosted = true;
            }
        }
        if (boosted) {
            break;
        }
        cout << "Cannot strength boost " << c << ", please enter a valid link to strength boost: ";
    }
    abilityUsed();
    cout << getName() << " has been used!" << endl;
}
