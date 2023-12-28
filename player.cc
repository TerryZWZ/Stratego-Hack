#include "player.h"
#include "linkbase.h"

Player::Player(int _id, Board *b, string inp) : 
    board{b},
    viruses{0}, 
    data{0},
    id{_id} {}

void Player::setOpponent(Player *o){
    opponent = o;
}

void Player::attach(shared_ptr<Observer> o) {
    if (o != nullptr) {
        observers.emplace_back(o);
    }
}

void Player::notifyObservers() {
    for (auto observer : observers) {
        observer->notifyInfo(abilityCount(), data, viruses, links, id);
    }
}

vector<shared_ptr<Link>> Player::getOpponentLinks() const {
    return opponent->links;
}

void Player::addAbility(const char& ability, int abilityID) {
    if (ability == 'L') { // Link Boost
        abilities.emplace_back(make_shared<LinkBoost>(abilityID, id, board, this));
        cout << "Added Ability " << abilityID << ": Link Boost" << endl;
    }
    else if (ability == 'F') { // Firewall
        abilities.emplace_back(make_shared<Firewall>(abilityID, id, board, this));
        cout << "Added Ability " << abilityID << ": Firewall" << endl;
    }
    else if (ability == 'D') { // Download
        abilities.emplace_back(make_shared<Download>(abilityID, id, board, this));
        cout << "Added Ability " << abilityID << ": Download" << endl;
    }
    else if (ability == 'S') { // Scan
        abilities.emplace_back(make_shared<Scan>(abilityID, id, board, this));
        cout << "Added Ability " << abilityID << ": Scan" << endl;
    }
    else if (ability == 'P') { // Polarize
        abilities.emplace_back(make_shared<Polarize>(abilityID, id, board, this));
        cout << "Added Ability " << abilityID << ": Polarize" << endl;
    }
    else if (ability == 'B') { // Strength Boost
        abilities.emplace_back(make_shared<StrengthBoost>(abilityID, id, board, this));
        cout << "Added Ability " << abilityID << ": Strength Boost" << endl;
    }
    else if (ability == 'E') { // Encrypt
        abilities.emplace_back(make_shared<Encrypt>(abilityID, id, board, this));
        cout << "Added Ability " << abilityID << ": Encrypt" << endl;
    }
    else if (ability == 'H') { // Hack
        abilities.emplace_back(make_shared<Hack>(abilityID, id, board, this));
        cout << "Added Ability " << abilityID << ": Hack" << endl;
    }
}

bool Player::useAbility(int abilityID, istream& in) {
    bool abilityExist = false;

    for (const auto& ability : abilities) {
        if (ability->getAbilityID() == abilityID) {
            // if ability is used
            if (ability->usage()) {
                cout << ability->getName() << " has already been used" << endl;
                abilityExist = true;
                return false;
            }
            else {
                ability->ability(links, in);
                abilityExist = true;
                return true;
            }
        }
    }
    if (!abilityExist) {
        cout << "Ability does not exist" << endl;
    }
    return false;
}

void Player::abilityList() {
    for (const auto& ability : abilities) {
        cout << ability->getAbilityID() << " - ";
        cout << ability->getName();

        if (ability->usage()) {
            cout << " [USED]" << endl;
        }
        else {
            cout << " [UNUSED]" << endl;
        }
    }
}

int Player::abilityCount() {
    int count = 0;

    for (const auto& ability : abilities) {
        if (!ability->usage()) {
            count++;
        }
    }
    return count;
}

void Player::addLink(char type, int strength, int col) {
    bool isData = (type == 'D'), mid = (col == 3 || col == 4);
    int row;
    if (id == 1) row = (mid ? 1 : 0);
    else row = (mid ? 6 : 7);
    char linkID = (id == 1 ?  'a' : 'A');
    auto link = make_shared<LinkBase>((char) linkID + col, strength, isData, id, row, col);
    links.emplace_back(static_pointer_cast<Link>(link));
    dynamic_cast<Tile*>(board->getCell(row, col))->occupyTile(static_pointer_cast<Link>(link));
}

// gets index of link in the links vector
int Player::getLink(char link) {
    for (unsigned int i = 0; i < links.size(); ++i) {
        if (links[i] && links[i]->getChar() == link) return i;
    }
    return -1;
}

bool Player::moveLink(char c, int x, int y) {
    // moving link c to coords (x, y)
    auto link = links[getLink(c)];
    int oldX = link->getX(), oldY = link->getY();
    link->setCoords(x, y);
    static_cast<Tile*>(board->getCell(oldX, oldY))->removeLink();
    board->getCell(oldX, oldY)->notifyObservers();
    static_cast<Tile*>(board->getCell(x, y))->occupyTile(link);
    board->getCell(x, y)->notifyObservers();
    return true;
}

void Player::removeLink(char c) {
    int linkNum = getLink(c);
    links[linkNum]->setDownloaded();
}

bool Player::moveLink(char c, Direction dir) {
        // check if chosen link is valid
        int linkNum = getLink(c);
        if (links[linkNum]->getDownloaded()) return false;
        if (linkNum == -1) return false;
        
        // move link from prevX, prevY to newX, newY
        int xlo = (id == 1 ? 0 : -5), xhi = (id == 1 ? board->boardSize + 5 : board->boardSize);
        int prevX = links[linkNum]->getX(), prevY = links[linkNum]->getY();
        int newX = prevX, newY = prevY;
        if (!links[linkNum]->move(dir, xlo, xhi, 0, board->boardSize, newX, newY)) return false;

        // check if is end of board
        if (newX < 0 || newX >= board->boardSize) {
            if (links[linkNum]->getIsData()) download(*links[linkNum]);
            else opponent->download(*links[linkNum]);
            static_cast<Tile*>(board->getCell(prevX, prevY))->removeLink();
            board->getCell(prevX, prevY)->notifyObservers();
            return true;
        }

        // check & handle battles
        auto targetTile = dynamic_cast<Tile*>(board->getCell(newX, newY));
        if (targetTile){
            auto targetLink = targetTile->getLink();
            if (targetLink != nullptr) {
                if (targetLink->getPlayerID() == id) {
                    return false;
                }
                else {
                    moveLink(c, newX, newY);
                    // if link still exists
                    if (!links[linkNum]) return true;
                    // check if both links are not downloaded already
                    if (!links[linkNum]->getDownloaded() && !targetLink->getDownloaded()) {
                        // compare strengths
                        if (*links[linkNum] > *targetLink) {
                            targetLink->reveal();
                            links[linkNum]->reveal();
                            board->getCell(links[linkNum]->getX(), links[linkNum]->getY())->notifyObservers();
                            download(*targetLink);
                            static_cast<Tile*>(board->getCell(newX, newY))->removeLink();
                            static_cast<Tile*>(board->getCell(newX, newY))->occupyTile(links[linkNum]);
                            board->getCell(newX, newY)->notifyObservers();
                        }
                        else {
                            targetLink->reveal();
                            links[linkNum]->reveal();
                            board->getCell(targetLink->getX(), targetLink->getY())->notifyObservers();
                            opponent->download(*links[linkNum]);
                            board->getCell(prevX, prevY)->notifyObservers();
                            static_cast<Tile*>(board->getCell(newX, newY))->occupyTile(targetLink);
                            board->getCell(newX, newY)->notifyObservers();
                        }
                    }
                    return true;
                }
            }
        }
        
        // check & handle for moving into server
        auto targetServer = dynamic_cast<Server*>(board->getCell(newX, newY));
        if (targetServer){
            if (targetServer->getPlayer() == id){ //friendly server, invalid move
                return false;
            }
            else{
                opponent->download(*links[linkNum]);
                static_cast<Tile*>(board->getCell(prevX, prevY))->removeLink();
                board->getCell(prevX, prevY)->notifyObservers();
                return true;
            }
        }
        moveLink(c, newX, newY);
        return true;
}

void Player::download(Link& l) {
    if (l.getIsData()) ++data;
    else ++viruses;
    l.reveal();
    l.setDownloaded();
    notifyObservers();
}

// link boost
void Player::setLink(char ch, shared_ptr<Link> link) {
    links[getLink(ch)] = link;
}

int Player::dataCount() const {
    return data;
}

int Player::virusCount() const {
    return viruses;
}
