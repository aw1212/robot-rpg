#include "robot.h"

constexpr int moveIncrement = 10;

////////////////////////////
///CONSTRUCTOR/DESTRUCTOR///
////////////////////////////

Robot::Robot() {
    robotFacingDirection = RobotFacingDirection::FRONT;
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

RobotFacingDirection Robot::getCurrentFacingDirection() {
    return robotFacingDirection;
}

void Robot::move(RobotMovingDirection movingDirection, bool shouldMove) {
    switch (movingDirection) {
        case RobotMovingDirection::RIGHT: {
            robotFacingDirection = RobotFacingDirection::RIGHT;
            robotSprite.setTexture(robotRightTexture);
            break;
        }
        case RobotMovingDirection::LEFT: {
            robotFacingDirection = RobotFacingDirection::LEFT;
            robotSprite.setTexture(robotLeftTexture);
            break;
        }
        case RobotMovingDirection::UP: {
            robotFacingDirection = RobotFacingDirection::BACK;
            robotSprite.setTexture(robotBackTexture);
            break;
        }
        case RobotMovingDirection::DOWN: {
            robotFacingDirection = RobotFacingDirection::FRONT;
            robotSprite.setTexture(robotFrontTexture);
            break;
        }
    }

    if (shouldMove) {
        move(movingDirection);
    }
}

void Robot::pickUpItem(Item &item) {
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

void Robot::move(const RobotMovingDirection movingDirection) {
    switch (movingDirection) {
        case RobotMovingDirection::RIGHT: {
            //robotSprite.setPosition(robotSprite.getPosition().x + moveIncrement, robotSprite.getPosition().y);
            robotSprite.move(moveIncrement, 0);
            break;
        }
        case RobotMovingDirection::LEFT: {
            //robotSprite.setPosition(robotSprite.getPosition().x - moveIncrement, robotSprite.getPosition().y);
            robotSprite.move(-moveIncrement, 0);
            break;
        }
        case RobotMovingDirection::UP: {
            //robotSprite.setPosition(robotSprite.getPosition().x, robotSprite.getPosition().y - moveIncrement);
            robotSprite.move(0, -moveIncrement);
            break;
        }
        case RobotMovingDirection::DOWN: {
            //robotSprite.setPosition(robotSprite.getPosition().x, robotSprite.getPosition().y + moveIncrement);
            robotSprite.move(0, moveIncrement);
            break;
        }
    }
}


