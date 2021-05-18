#ifndef ROBOTRPG_ITEM_H
#define ROBOTRPG_ITEM_H

#include <SFML/Graphics.hpp>

//TODO make subclasses of item for the different types (carryable, interactable, etc)
enum class CarryableItemType {
    RED_SHRINE_PIECE,
    BLUE_SHRINE_PIECE,
    YELLOW_SHRINE_PIECE
};

class Item {
private:
    sf::Texture itemTexture;
    sf::Sprite itemSprite;
    bool visible{false};
    CarryableItemType itemType;
    sf::Vector2f position;
    // Functions
    void initSprite(sf::Vector2<float> scale);
    std::string getTextureFile();
public:
    // Constructors/Destructors
    Item(CarryableItemType itemType, bool visible, sf::Vector2f position, sf::Vector2<float> scale);
    virtual ~Item();
    // Getters
    sf::Sprite& getItemSprite();
    bool isVisible() const;
    // Functions
    void updateSprite();
};

#endif //ROBOTRPG_ITEM_H
