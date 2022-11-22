#ifndef ROBOTRPG_BOARD_H
#define ROBOTRPG_BOARD_H

#include <SFML/Graphics.hpp>

class Board {
public:
    bool isNearIntersect(const sf::Rect<float>& rectangle1, sf::Rect<float> rectangle2);
};

#endif //ROBOTRPG_BOARD_H