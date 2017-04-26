#include "player.h"

Player::Player(int x, int y, std::string name, bool isFirst) :
    x(x), y(y),
    name(name),
    isFirst(isFirst)
{
}

Player::~Player() {
}
