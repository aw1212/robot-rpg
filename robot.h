#ifndef ROBOTRPG_ROBOT_H
#define ROBOTRPG_ROBOT_H

#include <SFML/Graphics.hpp>
#include "vector"
#include "item.h"

enum class RobotFacingDirection {
    LEFT,
    RIGHT,
    FRONT,
    BACK
};

enum class RobotMovingDirection {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Robot {
private:
    sf::Texture robotFrontTexture, robotBackTexture, robotLeftTexture, robotRightTexture;
    sf::Sprite robotSprite;
    RobotFacingDirection robotFacingDirection;
    // Functions
    void initSprite();
    void move(RobotMovingDirection movingDirection);
public:
    // Constructors/Destructors
    Robot();
    virtual ~Robot();
    // Getters
    sf::Sprite& getRobotSprite();
    // Functions
    RobotFacingDirection getCurrentFacingDirection();
    void move(RobotMovingDirection movingDirection, bool shouldMove);
    void pickUpItem(Item& item);
};

#endif //ROBOTRPG_ROBOT_H
