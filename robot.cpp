#include "robot.h"

constexpr int moveIncrement = 10;

////////////////////////////
///CONSTRUCTOR/DESTRUCTOR///
////////////////////////////

Robot::Robot() {
    initSprite();
}

Robot::~Robot() {
}

///////////////
///ACCESSORS///
///////////////

sf::Sprite& Robot::getRobotSprite() {
    return robotSprite;
}

////////////////////
///PUBLIC METHODS///
////////////////////

void Robot::updateSprite(const RobotDirection direction, bool canMove) {
    switch (direction) {
        case RobotDirection::RIGHT: {
            robotSprite.setTexture(robotRightTexture);
            break;
        }
        case RobotDirection::LEFT: {
            robotSprite.setTexture(robotLeftTexture);
            break;
        }
        case RobotDirection::UP: {
            robotSprite.setTexture(robotBackTexture);
            break;
        }
        case RobotDirection::DOWN: {
            robotSprite.setTexture(robotFrontTexture);
            break;
        }
    }

    if (canMove) {
        move(direction);
    }
}

/////////////////////
///PRIVATE METHODS///
/////////////////////

void Robot::initSprite() {
    if (!robotFrontTexture.loadFromFile("assets/robot_front.png")) {
        //return EXIT_FAILURE;
    }
    if (!robotBackTexture.loadFromFile("assets/robot_back.png")) {
        //return EXIT_FAILURE;
    }
    if (!robotLeftTexture.loadFromFile("assets/robot_left.png")) {
        //return EXIT_FAILURE;
    }
    if (!robotRightTexture.loadFromFile("assets/robot_right.png")) {
        //return EXIT_FAILURE;
    }

    robotSprite.setTexture(robotFrontTexture);
    robotSprite.setScale(0.5, 0.5);
    robotSprite.setPosition(0, 0);
}

void Robot::move(const RobotDirection direction) {
    switch (direction) {
        case RobotDirection::RIGHT: {
            robotSprite.setPosition(robotSprite.getPosition().x + moveIncrement, robotSprite.getPosition().y);
            break;
        }
        case RobotDirection::LEFT: {
            robotSprite.setPosition(robotSprite.getPosition().x - moveIncrement, robotSprite.getPosition().y);
            break;
        }
        case RobotDirection::UP: {
            robotSprite.setPosition(robotSprite.getPosition().x, robotSprite.getPosition().y - moveIncrement);
            break;
        }
        case RobotDirection::DOWN: {
            robotSprite.setPosition(robotSprite.getPosition().x, robotSprite.getPosition().y + moveIncrement);
            break;
        }
    }
}


