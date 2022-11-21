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
                               sf::Vector2(0.25f, 0.5f),
                               true,
                               false);

    Item* blueRectangle = new Item(ItemType::BLUE_RECTANGLE,
                               sf::Vector2f(200, 800),
                               sf::Vector2(0.25f, 0.5f),
                                   true,
                               true);

    Item* completedRedShrine = new Item(ItemType::RED_SHRINE_COMPLETE,
                                        sf::Vector2f(650, 550),
                                        sf::Vector2(0.25f, 0.5f),
                                        false,
                                        false);

    items.push_back(redShrine);
    items.push_back(blueRectangle);
    items.push_back(completedRedShrine);
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
            std::cout << "I'M CLICKABLE" << std::endl;

            const sf::Rect<float> itemBounds = item->getItemSprite().getGlobalBounds();
            if (itemBounds.contains(mousePosView)) {
                return item;
            }
        }
    }

    return nullptr;
}

bool Game::isItemClickable(Item& item) {
    return item.isVisible() &&
        robot.getRobotSprite().getGlobalBounds().intersects(item.getItemSprite().getGlobalBounds());
}

void Game::updateItem(Item* item) {
    // If the clicked on item is carriable (a shrine piece) then pick it up
    if (item->canBeCarried()) {
        robot.pickUpItem(*item);
    } else {
        // If the clicked on item is a shrine and we are holding the correct piece, put it in shrine
        item->updateSprite();
    }
}


