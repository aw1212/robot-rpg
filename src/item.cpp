#include <iostream>
#include "../include/item.h"

////////////////////////////
///CONSTRUCTOR/DESTRUCTOR///
////////////////////////////

Item::Item(ItemType itemType, sf::Vector2f position, sf::Vector2<float> scale, bool visible, bool carriable) :
    itemType{itemType}, visible{visible}, carriable{carriable}, position{position} {
    initSprite(scale);
}

ShrinePieceItem::ShrinePieceItem(ItemType itemType, sf::Vector2f position, sf::Vector2<float> scale, bool visible) :
    Item(itemType, position, scale, visible, true) {
}

ShrineItem::ShrineItem(ItemType itemType, sf::Vector2f position, sf::Vector2<float> scale, bool visible) :
    Item(itemType, position, scale, visible, false) {
}

DecoyItem::DecoyItem(ItemType itemType, sf::Vector2f position, sf::Vector2<float> scale) :
    Item(itemType, position, scale, true, false) {
}

///////////////
///ACCESSORS///
///////////////

sf::Sprite& Item::getItemSprite() {
    return itemSprite;
}

ItemType Item::getItemType() {
    return itemType;
}

bool Item::isVisible() const {
    return visible;
}

void Item::setVisible(bool setVisible) {
    visible = setVisible;
}

bool Item::canBeCarried() const {
    return carriable;
}

/////////////////////
///PRIVATE METHODS///
/////////////////////

void Item::initSprite(const sf::Vector2<float> scale) {
    std::string textureFile = getTextureFile();

    if (!itemTexture.loadFromFile(textureFile)) {
        std::cout << "CANT LOAD" << std::endl;
    }

    itemSprite.setTexture(itemTexture);
    itemSprite.setPosition(position.x, position.y);
    itemSprite.setScale(scale);
}

std::string Item::getTextureFile() {
    switch (itemType) {
        case ItemType::SHRINE:
            return "assets/red_shrine.png";
        case ItemType::SHRINE_PIECE:
            return "assets/blue_rectangle.png";
        case ItemType::COMPLETED_SHRINE:
            return "assets/red_shrine_with_object.png";
        case ItemType::DECOY_PIECE:
            return "assets/blue_rectangle.png";
        default:
            std::cout << "UNKNOWN ITEM TYPE" << std::endl;
            exit(1);
    }
}