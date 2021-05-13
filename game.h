#ifndef ROBOTRPG_GAME_H
#define ROBOTRPG_GAME_H

#include "robot.h"
#include "item.h"
#include <SFML/Graphics.hpp>
#include "vector"

class Game {
private:
    // Window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event event;
    // Mouse Positions (relative to game window)
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    // Game objects
    Robot robot;
    std::vector<Item*> items;
    // Functions
    void initWindow();
    void initItems();
    void pollEvents();
    void updateMousePosition();
    void updateRobot(RobotDirection direction);
    void updateItem();
    static bool canMove();
public:
    // Constructors/Destructors
    Game();
    virtual ~Game();
    // Functions
    bool isRunning();
    void update();
    void render();
};

#endif //ROBOTRPG_GAME_H
