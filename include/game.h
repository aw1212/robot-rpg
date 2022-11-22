#ifndef ROBOTRPG_GAME_H
#define ROBOTRPG_GAME_H

#include "robot.h"
#include "item.h"
#include <SFML/Graphics.hpp>
#include "vector"
#include "unordered_map"

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
    std::unordered_map<Item*, Item*> itemMap;
    // Functions
    void initWindow();
    void initItems();
    void pollEvents();
    void updateMousePosition();
    void updateRobot(const RobotMovingDirection movingDirection);
    Item* const clickedOnItem();
    bool isItemClickable(Item& item);
    void updateItem(Item* const item);
    bool shouldRobotMove(RobotMovingDirection movingDirection);
    bool shouldUpdateRobotPosition(RobotMovingDirection movingDirection);
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