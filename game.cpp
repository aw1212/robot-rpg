#include "game.h"
#include <iostream>

////////////////////////////
///CONSTRUCTOR/DESTRUCTOR///
////////////////////////////

Game::Game() {
    window = nullptr;
    initWindow();
    initItems();
//    initRobot();
}

Game::~Game() {
    delete window;
}

////////////////////
///PUBLIC METHODS///
////////////////////

bool Game::isRunning() {
    return window->isOpen();
}

void Game::update() {
    pollEvents();
    updateMousePosition();
    //std::cout << robot.getRobotSprite().getPosition().x << " " << robot.getRobotSprite().getPosition().y << std::endl;
}

void Game::render() {
    window->clear(sf::Color::White); // Clear old frame

    // Draw game
    window->draw(robot.getRobotSprite());

    for (auto item : items) {
        if (item->isVisible()) {
            window->draw(item->getItemSprite());
        }
    }

    // Displays - tell app that window is done drawing
    window->display();
}

/////////////////////
///PRIVATE METHODS///
/////////////////////

void Game::initWindow() {
    videoMode.height = 1400;
    videoMode.width = 1400;
    window = new sf::RenderWindow(videoMode, "Robotz", sf::Style::Titlebar | sf::Style::Close);
//    window->setFramerateLimit(144);
}

//void Game::initRobot() {
//
//}

void Game::initItems() {
    Item* redShrine = new Item(ItemType::RED_SHRINE,
                               sf::Vector2f(650, 550),
                               sf::Vector2(0.25f, 0.25f),
                               true,
                               false);

    Item* blueRectangle = new Item(ItemType::BLUE_RECTANGLE,
                               sf::Vector2f(200, 1000),
                               sf::Vector2(0.25f, 0.25f),
                                   true,
                               true);

    Item* completedRedShrine = new Item(ItemType::RED_SHRINE_COMPLETE,
                                        sf::Vector2f(650, 550),
                                        sf::Vector2(0.25f, 0.25f),
                                        false,
                                        false);

    items.push_back(redShrine);
    items.push_back(blueRectangle);
    items.push_back(completedRedShrine);

    itemMap.emplace(redShrine, completedRedShrine);
}

void Game::pollEvents() {
    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed: {
                window->close();
                break;
            }
            case sf::Event::KeyPressed: {
                sf::Keyboard::Key keyCode = event.key.code;
                if (keyCode == sf::Keyboard::Escape) {
                    window->close();
                }
                if (keyCode == sf::Keyboard::Right || keyCode == sf::Keyboard::S) {
                    updateRobot(RobotMovingDirection::RIGHT);
                }
                if (keyCode == sf::Keyboard::Left || keyCode == sf::Keyboard::A) {
                    updateRobot(RobotMovingDirection::LEFT);
                }
                if (keyCode == sf::Keyboard::Up || keyCode == sf::Keyboard::W) {
                    updateRobot(RobotMovingDirection::UP);
                }
                if (keyCode == sf::Keyboard::Down || keyCode == sf::Keyboard::D) {
                    updateRobot(RobotMovingDirection::DOWN);
                }
                break;
            }
            case sf::Event::MouseButtonPressed: {
                Item* item = clickedOnItem();
                if (item != nullptr) {
                    updateItem(item);
                }
                break;
            }
            default: {
                //TODO
            }
        }
    }
}

void Game::updateMousePosition() {
    mousePosWindow = sf::Mouse::getPosition(*window);
    mousePosView = window->mapPixelToCoords(mousePosWindow);

    // Print mouse position relative to the window
    //std::cout << "On Window: " << mousePosWindow.x << " " << mousePosWindow.y << std::endl;
}

void Game::updateRobot(const RobotMovingDirection movingDirection) {
    robot.updateFacingPosition(movingDirection);

    if (shouldRobotMove(movingDirection)) {
        robot.move(movingDirection);
    }
}

bool Game::shouldRobotMove(const RobotMovingDirection movingDirection) {
    // Robot needs to be within the bounds of the game window and not overlapping with and object
    const sf::Sprite robotSprite = robot.getRobotSprite();
    const sf::Vector2f robotPosition = robotSprite.getPosition();
    const sf::Rect<float> robotGlobalBounds = robotSprite.getGlobalBounds();
    const sf::Rect<float> robotLocalBounds = robotSprite.getLocalBounds();

    // robotPosition.x: starts at 0, increases by 10 when robot moves right
    // robotPosition.y: starts at 0, increases by 10 when robot moves down
    // robotGlobalBounds.top: starts at 0, increases by 10 when robot moves down
    // robotGlobalBounds.left: starts at 0, increases by 10 when robot moves right
    // robotGlobalBounds.width = 256
    // robotGlobalBounds.height = 256
    // robotLocalBounds.top = 0
    // robotLocalBounds.left = 0
    // robotLocalBounds.width = 512
    // robotLocalBounds.height = 512
    // window->getSize().x // 1600
    // window->getSize().y // 1400

    // If robot is at leftmost of screen it cannot move left
    if (robotPosition.x <= 0 && movingDirection == RobotMovingDirection::LEFT) {
        return false;
    }

    // If robot is at top of screen it cannot move up
    if (robotPosition.y <= 0 && movingDirection == RobotMovingDirection::UP) {
        return false;
    }

    // If robot is at rightmost of screen it cannot move right
    if (robotGlobalBounds.left + robotGlobalBounds.width >= window->getSize().y
            && movingDirection == RobotMovingDirection::RIGHT) {
        return false;
    }

    // If robot is at bottom of screen it cannot move down
    if (robotGlobalBounds.top + robotGlobalBounds.height >= window->getSize().x
            && movingDirection == RobotMovingDirection::DOWN) {
        return false;
    }

    // If robot is near an item, it cannot move into it
    for (Item* item : items) {

        if (item->isVisible()) {
            sf::Sprite itemSprite = item->getItemSprite();
            const sf::Rect<float> itemGlobalBounds = itemSprite.getGlobalBounds();

            //itemSprite.getGlobalBounds().left = 280
            //itemSprite.getGlobalBounds().top = 180
            //itemSprite.getGlobalBounds().height = 256
            //itemSprite.getGlobalBounds().width = 128

            //TODO this is utter shite need to update
            Robot movedRobot = robot;
            movedRobot.move(movingDirection);

            if (movedRobot.getRobotSprite().getGlobalBounds().intersects(itemGlobalBounds)) {
                return false;
            }
        }
    }

    return shouldUpdateRobotPosition(movingDirection);
}

bool Game::shouldUpdateRobotPosition(const RobotMovingDirection movingDirection) {
    // we only want to update the robots position (physically move it) when its
    // already facing the direction of the move
    RobotFacingDirection facingDirection = robot.getCurrentFacingDirection();

    return (facingDirection == RobotFacingDirection::LEFT && movingDirection == RobotMovingDirection::LEFT) ||
            (facingDirection == RobotFacingDirection::RIGHT && movingDirection == RobotMovingDirection::RIGHT) ||
            (facingDirection == RobotFacingDirection::FRONT && movingDirection == RobotMovingDirection::DOWN) ||
            (facingDirection == RobotFacingDirection::BACK && movingDirection == RobotMovingDirection::UP);
}

Item* Game::clickedOnItem() {
    // Determine if any clickable (visible and in-range) item was clicked on
    for (auto item : items) {
        if (isItemClickable(*item)) {
            const sf::Rect<float> itemBounds = item->getItemSprite().getGlobalBounds();
            if (itemBounds.contains(mousePosView)) {
                return item;
            }
        }
    }

    return nullptr;
}

bool nearIntersect(const sf::Rect<float>& rectangle1, sf::Rect<float> rectangle2);

bool Game::isItemClickable(Item& item) {
    if (!item.isVisible()) {
        return false;
    }

    return nearIntersect(robot.getRobotSprite().getGlobalBounds(), item.getItemSprite().getGlobalBounds());
}

bool nearIntersect(const sf::Rect<float>& rectangle1, sf::Rect<float> rectangle2) {
    // Rectangles with negative dimensions are allowed, so we must handle them correctly

    // Compute the min and max of the first rectangle on both axes
    float r1MinX = std::min(rectangle1.left, static_cast<float>(rectangle1.left + rectangle1.width));
    float r1MaxX = std::max(rectangle1.left, static_cast<float>(rectangle1.left + rectangle1.width));
    float r1MinY = std::min(rectangle1.top, static_cast<float>(rectangle1.top + rectangle1.height));
    float r1MaxY = std::max(rectangle1.top, static_cast<float>(rectangle1.top + rectangle1.height));

    // Compute the min and max of the second rectangle on both axes
    float r2MinX = std::min(rectangle2.left, static_cast<float>(rectangle2.left + rectangle2.width));
    float r2MaxX = std::max(rectangle2.left, static_cast<float>(rectangle2.left + rectangle2.width));
    float r2MinY = std::min(rectangle2.top, static_cast<float>(rectangle2.top + rectangle2.height));
    float r2MaxY = std::max(rectangle2.top, static_cast<float>(rectangle2.top + rectangle2.height));

    // Compute the intersection boundaries
    float interLeft = std::max(r1MinX, r2MinX);
    float interTop = std::max(r1MinY, r2MinY);
    float interRight = std::min(r1MaxX, r2MaxX) + 20;
    float interBottom = std::min(r1MaxY, r2MaxY) + 20;

    // If the intersection is valid (positive non zero area), then there is an intersection
    if ((interLeft < interRight) && (interTop < interBottom)) {
        return true;
    }

    return false;
}

void Game::updateItem(Item* item) {
    // If the clicked on item is carriable (a shrine piece) then pick it up
    if (item->canBeCarried()) {
        robot.pickUpItem(*item);
        item->setVisible(false);
    } else {
        // If the clicked on item is a shrine and we are holding the correct piece, put it in shrine
        if (item->getItemType() == ItemType::RED_SHRINE) {

            if (!robot.isHoldingItem()) {
                return;
            }

            item->setVisible(false);
            auto it = itemMap.find(item);

            if (it != itemMap.end()) {
                it->second->setVisible(true);
            };
        }
        robot.holdItem(false);
        robot.updateRobotSprite();

        robot.setWin();
    }
}


