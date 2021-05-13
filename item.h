#ifndef ROBOTRPG_ITEM_H
#define ROBOTRPG_ITEM_H

#include <SFML/Graphics.hpp>

class Item {
private:
    sf::Texture itemTexture;
    sf::Sprite itemSprite;
    bool visible{false};
    // Functions
    void initSprite(const std::string& textureFile);
public:
    // Constructors/Destructors
    Item(const std::string& textureFile, bool visible);
    virtual ~Item();
    // Getters
    sf::Sprite& getItemSprite();
    bool isVisible();
    // Functions
    void updateSprite();
};

#endif //ROBOTRPG_ITEM_H
