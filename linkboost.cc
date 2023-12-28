#include "linkboost.h"
#include "player.h"

using namespace std;

LinkBoost::LinkBoost(int id, int playerID, Board* board, Player* player) : Ability(id, playerID, "Link Boost", board, player) {}

void LinkBoost::ability(vector<shared_ptr<Link>> links, istream& in) {
    char ch;
    bool existence = false;
    cout << "Link to link boost: ";
    while (in >> ch) {
        // can only link boost own links
        for (unsigned int i = 0; i < links.size(); ++i) {
            if (links[i] && links[i]->getChar() == ch && !(links[i]->getDownloaded())) {
                shared_ptr<Link> link = links[i];
                shared_ptr<LinkBoostDecorator> linkBoost = make_shared<LinkBoostDecorator>(links[i]);
                player->setLink(ch, linkBoost);
                existence = true;
            }
        }
        if (existence) {
            break;
        }
        cout << "Cannot link boost " << ch << ", please enter a valid link to boost: ";
    }
    abilityUsed();
    cout << getName() << " has been used!" << endl;
}
