#include <iostream>
#include "item.h"

////////////////////////////
///CONSTRUCTOR/DESTRUCTOR///
////////////////////////////

Item::Item(ItemType itemType, sf::Vector2f position, sf::Vector2<float> scale, bool visible, bool carriable) {
    this->itemType = itemType;
    this->visible = visible;
    this->carriable = carriable;
    this->position = position;
    initSprite(scale);
}

Item::~Item() {
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

////////////////////
///PUBLIC METHODS///
////////////////////

void Item::updateSprite() {

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
        case ItemType::RED_SHRINE:
            return "assets/red_shrine.png";
        case ItemType::BLUE_SHRINE:
            return "assets/blue_shrine.png";
        case ItemType::YELLOW_SHRINE:
            return "assets/yellow_shrine.png";
        case ItemType::BLUE_RECTANGLE:
            return "assets/blue_rectangle.png";
        case ItemType::RED_SHRINE_COMPLETE:
            return "assets/red_shrine_with_object.png";
    }
}