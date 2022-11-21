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

bool Robot::isHoldingItem() {
    return holdingItem;
}

void Robot::holdItem(bool isHoldingItem) {
    holdingItem = isHoldingItem;
}

RobotFacingDirection Robot::getCurrentFacingDirection() {
    return robotFacingDirection;
}

void Robot::updateFacingPosition(RobotMovingDirection movingDirection) {
    switch (movingDirection) {
        case RobotMovingDirection::RIGHT: {
            robotFacingDirection = RobotFacingDirection::RIGHT;
            break;
        }
        case RobotMovingDirection::LEFT: {
            robotFacingDirection = RobotFacingDirection::LEFT;
            break;
        }
        case RobotMovingDirection::UP: {
            robotFacingDirection = RobotFacingDirection::BACK;
            break;
        }
        case RobotMovingDirection::DOWN: {
            robotFacingDirection = RobotFacingDirection::FRONT;
            break;
        }
    }

    updateRobotSprite();
}

void Robot::updateRobotSprite() {
    switch (robotFacingDirection) {
        case RobotFacingDirection::RIGHT: {
            if (isHoldingItem()) {
                robotSprite.setTexture(robotRightItemTexture);
            } else {
                robotSprite.setTexture(robotRightTexture);
            }

            break;
        }
        case RobotFacingDirection::LEFT: {
            if (isHoldingItem()) {
                robotSprite.setTexture(robotLeftItemTexture);
            } else {
                robotSprite.setTexture(robotLeftTexture);
            }

            break;
        }
        case RobotFacingDirection::BACK: {
            if (isHoldingItem()) {
                robotSprite.setTexture(robotBackItemTexture);
            } else {
                robotSprite.setTexture(robotBackTexture);
            }

            break;
        }
        case RobotFacingDirection::FRONT: {
            if (isHoldingItem()) {
                robotSprite.setTexture(robotFrontItemTexture);
            } else {
                robotSprite.setTexture(robotFrontTexture);
            }

            break;
        }
    }
}

void Robot::pickUpItem(Item &item) {
    switch (robotFacingDirection) {
        case RobotFacingDirection::FRONT:
            robotSprite.setTexture(robotFrontItemTexture);
            break;
        case RobotFacingDirection::BACK:
            robotSprite.setTexture(robotBackItemTexture);
            break;
        case RobotFacingDirection::LEFT:
            robotSprite.setTexture(robotLeftItemTexture);
            break;
        case RobotFacingDirection::RIGHT:
            robotSprite.setTexture(robotRightItemTexture);
            break;
    }

    holdItem(true);
}

void Robot::setWin() {
    robotSprite.setTexture(robotWinTexture);
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
    if (robotFrontItemTexture.loadFromFile("assets/robot_front_with_blue_rect.png")) {
        //return EXIT_FAILURE;
    }
    if (robotBackItemTexture.loadFromFile("assets/robot_back_with_blue_rect.png")) {
        //return EXIT_FAILURE;
    }
    if (robotLeftItemTexture.loadFromFile("assets/robot_left_with_blue_rect.png")) {
        //return EXIT_FAILURE;
    }
    if (robotRightItemTexture.loadFromFile("assets/robot_right_with_blue_rect.png")) {
        //return EXIT_FAILURE;
    }
    if (robotWinTexture.loadFromFile("assets/robot_win.png")) {
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


