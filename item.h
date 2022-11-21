#ifndef ROBOTRPG_ITEM_H
#define ROBOTRPG_ITEM_H

#include <SFML/Graphics.hpp>

//TODO make subclasses of item for the different types (carryable, interactable, etc)
enum class ItemType {
    RED_SHRINE,
    BLUE_SHRINE,
    YELLOW_SHRINE,
    BLUE_RECTANGLE,
    RED_SHRINE_COMPLETE,
};

class Item {
private:
    sf::Texture itemTexture;
    sf::Sprite itemSprite;
    ItemType itemType;
    bool visible;
    bool carriable;
    sf::Vector2f position;
    // Functions
    void initSprite(sf::Vector2<float> scale);
    std::string getTextureFile();
public:
    // Constructors/Destructors
    Item(ItemType itemType, sf::Vector2f position, sf::Vector2<float> scale, bool visible, bool carriable);
    virtual ~Item();

    // Getters
    ItemType getItemType();
    sf::Sprite& getItemSprite();
    bool canBeCarried() const;
    bool isVisible() const;

    // Setters
    void setVisible(bool setVisible);

    // Functions
    void updateSprite();
};

#endif //ROBOTRPG_ITEM_H
