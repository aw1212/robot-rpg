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
    Item* shrineSquare = new Item("assets/shrine_square.png", true);
    items.push_back(shrineSquare);
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
                    updateRobot(RobotDirection::RIGHT);
                }
                if (keyCode == sf::Keyboard::Left || keyCode == sf::Keyboard::A) {
                    updateRobot(RobotDirection::LEFT);
                }
                if (keyCode == sf::Keyboard::Up || keyCode == sf::Keyboard::W) {
                    updateRobot(RobotDirection::UP);
                }
                if (keyCode == sf::Keyboard::Down || keyCode == sf::Keyboard::D) {
                    updateRobot(RobotDirection::DOWN);
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

void Game::updateRobot(const RobotDirection direction) {
    robot.updateSprite(direction, canMove());
}

bool Game::canMove() {
    return true;
}

void Game::updateItem() {

}


