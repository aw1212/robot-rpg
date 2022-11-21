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
    sf::Texture robotFrontItemTexture, robotBackItemTexture, robotLeftItemTexture, robotRightItemTexture;
    sf::Texture robotWinTexture;
    sf::Sprite robotSprite;
    RobotFacingDirection robotFacingDirection;

    bool holdingItem;

    // Functions
    void initSprite();
public:
    // Constructors/Destructors
    Robot();
    virtual ~Robot();
    // Getters
    sf::Sprite& getRobotSprite();
    bool isHoldingItem();
    // Setters
    void holdItem(bool isHoldingItem);
    // Functions
    void setWin();
    RobotFacingDirection getCurrentFacingDirection();
    void updateFacingPosition(RobotMovingDirection movingDirection);
    void updateRobotSprite();
    void move(RobotMovingDirection movingDirection);
    void pickUpItem(Item& item);
};

#endif //ROBOTRPG_ROBOT_H
