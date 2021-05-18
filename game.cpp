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

    for (auto i : items) {
        if (i->isVisible()) {
            window->draw(i->getItemSprite());
        }
    }

    // Displays - tell app that window is done drawing
    window->display();
}

/////////////////////
///PRIVATE METHODS///
/////////////////////

void Game::initWindow() {
    videoMode.height = 1600;
    videoMode.width = 1600;
    window = new sf::RenderWindow(videoMode, "Robotz", sf::Style::Titlebar | sf::Style::Close);
//    window->setFramerateLimit(144);
}

//void Game::initRobot() {
//
//}

void Game::initItems() {
    Item* redShrine = new Item(CarryableItemType::RED_SHRINE_PIECE, true, sf::Vector2f(280, 180), sf::Vector2(0.25f, 0.5f));
    items.push_back(redShrine);

    Item* blueShrine = new Item(CarryableItemType::BLUE_SHRINE_PIECE, false, sf::Vector2f(860, 860), sf::Vector2(0.25f, 0.5f));
    items.push_back(blueShrine);

    Item* yellowShrine = new Item(CarryableItemType::YELLOW_SHRINE_PIECE, false, sf::Vector2f(500, 500), sf::Vector2(0.25f, 0.5f));
    items.push_back(yellowShrine);
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
    robot.move(movingDirection, shouldRobotMove(movingDirection));
}

bool Game::shouldRobotMove(const RobotMovingDirection movingDirection) {
    // Robot needs to be within the bounds of the game window and not overlapping with and object
    const sf::Vector2f robotPosition = robot.getRobotSprite().getPosition();

    // If robot is at leftmost of screen it cannot move left
    if (robotPosition.x == 0 && movingDirection == RobotMovingDirection::LEFT) {
        return false;
    }

    // If robot is at top of screen it cannot move up
    if (robotPosition.y == 0 && movingDirection == RobotMovingDirection::UP) {
        return false;
    }

    // If robot is at rightmost of screen it cannot move right
    //TODO this doesnt seem to work correctly
    if (robotPosition.x == window->getSize().x && movingDirection == RobotMovingDirection::RIGHT) {
        return false;
    }

    // If robot is at bottom of screen it cannot move right
    if (robotPosition.x == window->getSize().y && movingDirection == RobotMovingDirection::DOWN) {
        return false;
    }

    return shouldUpdateRobotPosition(movingDirection);

    //TODO overlapping objects?
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
    // If the clicked on item is carryable (a shrine piece) then pick it up
    robot.pickUpItem(*item);

    // If the clicked on item is a shrine and we are holding the correct piece, put it in shrine
    item->updateSprite();
}


