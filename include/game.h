#ifndef ROBOTRPG_GAME_H
#define ROBOTRPG_GAME_H

#include "robot.h"
#include "item.h"
#include "board.h"
#include <SFML/Graphics.hpp>
#include "vector"
#include "unordered_map"

class Game {
    using LevelItemMap = std::unordered_map<int, std::vector<Item*>>;
public:
    // Constructors/Destructors
    Game();
    virtual ~Game();
    // Functions
    bool isRunning();
    void update();
    void renderBoard();
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
    LevelItemMap items;
    std::unordered_map<int, Item*> itemMap;
    sf::Font font;
    sf::Text text;
    // Game Board
    Board board;
    // Game state
    bool gameWon;
    int frame = 0;
    int level = 1;
    bool levelUp = false;
    // Functions
    void initWindow();
    void initItems();
    void initRobot();
    void pollEvents();
    void updateMousePosition();
    void updateRobot(const RobotMovingDirection movingDirection);
    Item* clickedOnItem();
    bool isItemClickable(Item& item);
    void updateItem(Item* const item);
    bool shouldRobotMove(RobotMovingDirection movingDirection);
    bool shouldUpdateRobotPosition(RobotMovingDirection movingDirection);
    void mouseClicked();
    void loadBackground();
};

#endif //ROBOTRPG_GAME_H
