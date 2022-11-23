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
public:
    // Getters
    sf::Sprite& getRobotSprite();
    const bool isHoldingItem() const;
    // Setters
    void holdItem(const bool isHoldingItem);
    // Functions
    void setDefaultTexture();
    void setWinTexture();
    RobotFacingDirection getCurrentFacingDirection();
    void updateFacingPosition(const RobotMovingDirection movingDirection);
    void updateRobotSprite();
    void move(const RobotMovingDirection movingDirection);
    void pickUpItem(const Item& item);
    void initSprite();
private:
    sf::Texture robotFrontTexture, robotBackTexture, robotLeftTexture, robotRightTexture;
    sf::Texture robotFrontItemTexture, robotBackItemTexture, robotLeftItemTexture, robotRightItemTexture;
    sf::Texture robotWinTexture;
    sf::Sprite robotSprite;
    RobotFacingDirection robotFacingDirection;
    bool holdingItem;
};

#endif //ROBOTRPG_ROBOT_H
