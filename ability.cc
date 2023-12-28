#include "ability.h"
#include "player.h"

Ability::Ability(int abilityID, int playerID, const string& name, Board* board, Player* player):
    abilityID{abilityID}, playerID{playerID}, name{name}, board{board}, player{player}, used{false} {}

string Ability::getName() const {
    return name;
}

bool Ability::usage() const {
    return used;
}

void Ability::abilityUsed() {
    used = true;
}

int Ability::getAbilityID() const {
    return abilityID;
}

int Ability::getPlayerID() const {
    return playerID;
}
