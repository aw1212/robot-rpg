#include "../include/game.h"
#include <iostream>

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
    // Clear old frame
    //sf::Color windowColor = gameWon ? sf::Color(229, 204, 255, 255) : sf::Color(215, 241, 191, 255);
    //window->clear(windowColor);
    window->clear();

    // Draw background
    sf::Texture backgroundCity;
    if (!backgroundCity.loadFromFile("assets/future_wallpaper.png")) {
        std::cout << "CANT LOAD BACKGROUND CITY" << std::endl;
        exit(1);
    }

    sf::Sprite backgroundCitySprite;
    backgroundCitySprite.setTexture(backgroundCity);
    backgroundCitySprite.setPosition(-250, 0);
    window->draw(backgroundCitySprite);

//    sf::Texture shrineBackground;
//    if (!shrineBackground.loadFromFile("assets/background.jpg")) {
//        std::cout << "CANT LOAD SHRINE BACKGROUND" << std::endl;
//        exit(1);
//    }
//
//    sf::Sprite shrineBackgroundSprite;
//    shrineBackgroundSprite.setTexture(shrineBackground);
//    shrineBackgroundSprite.setPosition(560, 370);
//    window->draw(shrineBackgroundSprite);

    // Draw robot
    window->draw(robot.getRobotSprite());

    // Draw items
    for (auto item : items) {
        if (item->isVisible()) {
            window->draw(item->getItemSprite());
        }
    }

    if (gameWon) {
        sf::Font font;
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
        text.setFillColor(sf::Color::Red);

        // set position
        text.setPosition(100, 5);

        // set letter spacing
        text.setLetterSpacing(2);

        // set the text style
        text.setStyle(sf::Text::Bold);

        window->setFramerateLimit(100);
        if (frame % 2 == 0) {
            robot.setWinTexture();
        } else {
            robot.setDefaultTexture();
        }

        frame++;
        window->draw(text);
    }

    // Displays - tell program that window is done drawing
    window->display();
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
    Item* redShrine = new ShrineItem(ItemType::RED_SHRINE,
                                 sf::Vector2f(650, 660),
                               sf::Vector2(0.25f, 0.25f),
                               true);

    Item* blueRectangle = new ShrineObjectItem(ItemType::BLUE_RECTANGLE,
                               sf::Vector2f(100, 810),
                               sf::Vector2(0.25f, 0.25f),
                               true);

    Item* completedRedShrine = new ShrineItem(ItemType::RED_SHRINE_COMPLETE,
                                    sf::Vector2f(650, 660),
                                        sf::Vector2(0.25f, 0.25f),
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

bool Game::isItemClickable(Item& item) {
    if (!item.isVisible()) {
        return false;
    }

    return board.isNearIntersect(robot.getRobotSprite().getGlobalBounds(), item.getItemSprite().getGlobalBounds());
}

void Game::updateItem(Item* const item) {
    // If the clicked on item is carriable (a shrine piece) then pick it up
    if (item->canBeCarried()) {
        robot.pickUpItem(*item);
        item->setVisible(false);
    } else {
        // If the clicked on item is a shrine and we are holding the correct piece, put it in shrine
        //TODO dont hardcode the shrine pieces or move this logic to somewhere else
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

        gameWon = true;
    }
}



