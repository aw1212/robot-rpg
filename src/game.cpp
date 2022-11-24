#include "game.h"
#include <iostream>
#include "string"
#include <unistd.h>
#include <random>
#include <chrono>
#include <thread>

////////////////////////////
///CONSTRUCTOR/DESTRUCTOR///
////////////////////////////

Game::Game() {
    window = nullptr;
    initWindow();
    initRobot();
    initItems();
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
    updateMousePosition();;
}

void Game::renderBoard() {
    window->clear();

    // Draw background
    loadBackground();

    // Draw robot
    window->draw(robot.getRobotSprite());

    // Draw items
    auto it = items.find(level);
    if (it != items.end()) {
        for (auto item : it->second) {
            if (item->isVisible()) {
                window->draw(item->getItemSprite());
            }
        }
    }

    if (levelUp) {
        level++;
    }

    if (level == 3) {
        gameWon = true;
    }

    //TODO add level text
    if (gameWon) {
        if (!font.loadFromFile("assets/fonts/AlexBrush-Regular.ttf")) {
            std::cout << "CANT LOAD FONT" << std::endl;
            exit(1);
        }

        // select the font
        text.setFont(font);

        // set the string to display
        text.setString("YOU WON");

        // set the character size (in pixels, not points!)
        text.setCharacterSize(200);

        // set the color
        text.setFillColor(sf::Color(204, 0, 102, 255));

        // set position
        text.setPosition(100, 150);

        // set letter spacing
        text.setLetterSpacing(2);

        // set the text style
        text.setStyle(sf::Text::Bold);

        window->setFramerateLimit(100);
        if (frame % 2 == 0) {
            robot.setWin();
        } else {
            robot.setDefaultTexture();
        }

        frame++;
    } else {
        //set level title
        if (!font.loadFromFile("assets/fonts/Roboto-Black.ttf")) {
            std::cout << "CANT LOAD FONT" << std::endl;
            exit(1);
        }

        // select the font
        text.setFont(font);

        // set the string to display
        text.setString("LEVEL " + std::to_string(level));

        // set the character size (in pixels, not points!)
        text.setCharacterSize(50);

        // set position
        text.setPosition(1170, 10);

        // set the text style
        text.setStyle(sf::Text::Bold);
    }

    window->draw(text);

    // Displays - tell program that window is done drawing
    window->display();

    if (levelUp) {
        if (!gameWon) {
            robot.setDefault();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        levelUp = false;
    }
}

void Game::loadBackground() {
    std::unordered_map<int, std::string> backgroundMap;
    backgroundMap.emplace(1, "assets/future_wallpaper.png");
    backgroundMap.emplace(2, "assets/future_wallpaper.png");
    backgroundMap.emplace(3, "assets/future_wallpaper.png");

    auto it = backgroundMap.find(level);

    if (it != backgroundMap.end()) {
        sf::Texture backgroundCity;
        if (!backgroundCity.loadFromFile(it->second)) {
            std::cout << "CANT LOAD BACKGROUND CITY" << std::endl;
            exit(1);
        }

        sf::Sprite backgroundCitySprite;
        backgroundCitySprite.setTexture(backgroundCity);
        backgroundCitySprite.setPosition(-250, 0);
        window->draw(backgroundCitySprite);
    }
}

/////////////////////
///PRIVATE METHODS///
/////////////////////

void Game::initWindow() {
    videoMode.height = 1000;
    videoMode.width = 1400;
    window = new sf::RenderWindow(videoMode, "Robotz", sf::Style::Titlebar | sf::Style::Close);
//    window->setFramerateLimit(144);
}

void Game::initRobot() {
    robot.initSprite();
}

void Game::initItems() {
    std::vector<Item*> level1Items;

    Item* level1RedShrine = new ShrineItem(ItemType::SHRINE,
                               sf::Vector2f(650, 660),
                               sf::Vector2(0.25f, 0.25f),
                               true);

    Item* level1BlueRectangle = new ShrinePieceItem(ItemType::SHRINE_PIECE,
                                        sf::Vector2f(100, 810),
                                        sf::Vector2(0.25f, 0.25f),
                                        true);

    Item* level1CompletedRedShrine = new ShrineItem(ItemType::COMPLETED_SHRINE,
                                        sf::Vector2f(650, 660),
                                        sf::Vector2(0.25f, 0.25f),
                                        false);

    level1Items.push_back(level1RedShrine);
    level1Items.push_back(level1BlueRectangle);
    level1Items.push_back(level1CompletedRedShrine);

    std::vector<Item*> level2Items;

    Item* level2Shrine = new ShrineItem(ItemType::SHRINE,
                                        sf::Vector2f(650, 660),
                                        sf::Vector2(0.25f, 0.25f),
                                        true);

    Item* level2ShrineItem = new ShrinePieceItem(ItemType::SHRINE_PIECE,
                                                 sf::Vector2f(812, 27),
                                                 sf::Vector2(0.25f, 0.25f),
                                                 true);

    Item* level2CompletedShrine = new ShrineItem(ItemType::COMPLETED_SHRINE,
                                                 sf::Vector2f(650, 660),
                                                 sf::Vector2(0.25f, 0.25f),
                                                 false);

    level2Items.push_back(level2Shrine);
    level2Items.push_back(level2ShrineItem);
    level2Items.push_back(level2CompletedShrine);

    for (int i = 0; i < 5; i++) {
        std::uniform_int_distribution<int> intDistroX(100,1200);
        std::default_random_engine defEngineX(i + 1);

        std::uniform_int_distribution<int> intDistroY(100,1400);
        std::default_random_engine defEngineY(i + 2);

        int valX = intDistroX(defEngineX);
        int valY = intDistroY(defEngineY);

        std::cout << "X value: " << valX << std::endl;
        std::cout << "Y value: " << valY << std::endl;

        Item* level2DecoyItem = new DecoyItem(ItemType::DECOY_PIECE,
                                  sf::Vector2f(valX, valY),
                                  sf::Vector2(0.25f, 0.25f));

        level2Items.push_back(level2DecoyItem);
    }

    itemMap.emplace(1, level1CompletedRedShrine);
    itemMap.emplace(2, level2CompletedShrine);
    items.emplace(1, level1Items);
    items.emplace(2, level2Items);
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
                if (keyCode == sf::Keyboard::Space || keyCode == sf::Keyboard::Enter) {
                    mouseClicked();
                }
                break;
            }
            case sf::Event::MouseButtonPressed: {
                mouseClicked();
                break;
            }
            default: {
                //std::cout << "UNKNOWN KEY PRESSED" << std::endl;
            }
        }
    }
}

void Game::mouseClicked() {
    Item* const item = clickedOnItem();
    if (item != nullptr) {
        updateItem(item);
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
    auto it = items.find(level);

    if (it != items.end()) {
        for (Item* item : it->second) {

            if (item->isVisible()) {
                sf::Sprite itemSprite = item->getItemSprite();
                const sf::Rect<float> itemGlobalBounds = itemSprite.getGlobalBounds();

                //TODO this is utter shit need to update
                // Need to see if the robot *would* end up intersecting but cannot move it or it will
                // stay stuck and unable to move.
                Robot movedRobot = robot;
                movedRobot.move(movingDirection);

                if (movedRobot.getRobotSprite().getGlobalBounds().intersects(itemGlobalBounds)) {
                    return false;
                }
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
    auto it = items.find(level);

    if (it != items.end()) {
        for (auto item : it->second) {
            if (isItemClickable(*item)) {
                const sf::Rect<float> itemBounds = item->getItemSprite().getGlobalBounds();
                if (itemBounds.contains(mousePosView)) {
                    return item;
                }
            }
        }
    }

    return nullptr;
}

bool Game::isItemClickable(Item& item) {
    if (!item.isVisible()) {
        return false;
    }

    return board.isNearIntersect(robot.getRobotSprite().getGlobalBounds(), item.getItemSprite().getGlobalBounds());
}

void Game::updateItem(Item* const item) {
    if (item->getItemType() == ItemType::DECOY_PIECE) {
        return;
    }

    // If the clicked on item is carriable (a shrine piece) then pick it up
    if (item->canBeCarried()) {
        robot.pickUpItem(*item);
        item->setVisible(false);
    } else {
        // If the clicked on item is a shrine and we are holding the correct piece, put it in shrine
        //TODO dont hardcode the shrine pieces or move this logic to somewhere else
        if (item->getItemType() == ItemType::SHRINE) {
            if (!robot.isHoldingItem()) {
                return;
            }

            item->setVisible(false);
            auto it = itemMap.find(level);

            if (it != itemMap.end()) {
                it->second->setVisible(true);
            } else {
                std::cout << "CANT FIND ITEM MAP ITEM" << std::endl;
            }
        }

        robot.holdItem(false);
        robot.updateRobotSprite();
        levelUp = true;
    }
}



