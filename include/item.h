#ifndef ROBOTRPG_ITEM_H
#define ROBOTRPG_ITEM_H

#include <SFML/Graphics.hpp>

enum class ItemType {
    SHRINE,
    SHRINE_PIECE,
    COMPLETED_SHRINE,
    DECOY_PIECE
};

class Item {
public:
    // Constructors/Destructors
    Item(ItemType itemType, sf::Vector2f position, sf::Vector2<float> scale, bool visible, bool carriable);
    virtual ~Item() = default;

    // Getters
    ItemType getItemType();
    sf::Sprite& getItemSprite();
    bool canBeCarried() const;
    bool isVisible() const;

    // Setters
    void setVisible(bool setVisible);
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
};

class ShrinePieceItem : public Item {
public:
    // Constructors/Destructors
    ShrinePieceItem(ItemType itemType, sf::Vector2f position, sf::Vector2<float> scale, bool visible);
    virtual ~ShrinePieceItem() = default;
};

class ShrineItem : public Item {
public:
    // Constructors/Destructors
    ShrineItem(ItemType itemType, sf::Vector2f position, sf::Vector2<float> scale, bool visible);
    virtual ~ShrineItem() = default;
};

class DecoyItem : public Item {
public:
    // Constructors/Destructors
    DecoyItem(ItemType itemType, sf::Vector2f position, sf::Vector2<float> scale);
    virtual ~DecoyItem() = default;
};

#endif //ROBOTRPG_ITEM_H
