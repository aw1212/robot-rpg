#ifndef ROBOTRPG_ROBOT_H
#define ROBOTRPG_ROBOT_H

#include <SFML/Graphics.hpp>
#include "vector"

enum class RobotDirection {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Robot {
private:
    sf::Texture robotFrontTexture, robotBackTexture, robotLeftTexture, robotRightTexture;
    sf::Sprite robotSprite;
    // Functions
    void initSprite();
    void move(RobotDirection direction);
public:
    // Constructors/Destructors
    Robot();
    virtual ~Robot();
    // Getters
    sf::Sprite& getRobotSprite();
    // Functions
    void updateSprite(RobotDirection direction, bool canMove);
};

#endif //ROBOTRPG_ROBOT_H
