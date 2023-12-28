#include "direction.h"

Direction toDirection(std::string &s){
    if (s == "up") return Direction::Up;
    if (s == "down") return Direction::Down;
    if (s == "left") return Direction::Left;
    if (s == "right") return Direction::Right;
    return Direction::Stand;
}
