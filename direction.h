#ifndef __DIRECTION_H_
#define __DIRECTION_H_

#include <string>
#include <iostream>

// categorizes direction into enum class; used to process moves
enum class Direction {
    Stand,
    Up,
    Down,
    Left,
    Right
};

Direction toDirection(std::string &s);

#endif
