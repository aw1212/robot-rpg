#ifndef ROBOTRPG_BOARD_H
#define ROBOTRPG_BOARD_H

#include <SFML/Graphics.hpp>

class Board {
public:
    bool isNearIntersect(const sf::Rect<float>& rectangle1, sf::Rect<float> rectangle2);
private:
    const int nearIntersectDistance = 10;
};

#endif //ROBOTRPG_BOARD_H