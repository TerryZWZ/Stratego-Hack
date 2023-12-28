#include "link.h"

using namespace std;

Link::Link() {}
 
Link::Link(char _id, int _str, bool _data, int _pID, int r, int c): 
    linkID{_id}, strength{_str}, isData{_data}, playerID{_pID}, x{r}, y{c} {}

void Link::setCoords(int _r, int _c) {
    x = _r; 
    y = _c;
}

bool Link::getHidden() const {
    return hidden;
}

bool Link::getIsEncrypted() const {
    return isEncrypted;
}

void Link::encrypt() {
    isEncrypted = true;
}

void Link::reveal() {
    this->hidden = false;
}

char Link::getChar() const {
    return linkID;
}

int Link::getStrength() const {
    return strength;
}

int Link::getPlayerID() const {
    return playerID;
}

int Link::getX() const {
    return x;
}

int Link::getY() const {
    return y;
}

bool Link::getIsData() const {
    return isData;
}

void Link::polarize() {
    isData = !(isData);
}

void Link::strengthBoost() {
    ++strength;
}

bool Link::getDownloaded() const {
    return downloaded;
}

void Link::setDownloaded() {
    downloaded = true;
}

bool Link::operator>(Link &other) {
    return strength >= other.strength;
}
