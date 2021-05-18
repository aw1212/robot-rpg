#include "item.h"

////////////////////////////
///CONSTRUCTOR/DESTRUCTOR///
////////////////////////////

Item::Item(CarryableItemType itemType, bool visible, sf::Vector2f position, sf::Vector2<float> scale) {
    this->visible = visible;
    this->position = position;
    this->itemType = itemType;
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

bool Item::isVisible() const {
    return visible;
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
        //return EXIT_FAILURE;
    }

    itemSprite.setTexture(itemTexture);
    itemSprite.setPosition(position.x, position.y);
    itemSprite.setScale(scale);
}

std::string Item::getTextureFile() {
    switch (itemType) {
        case CarryableItemType::RED_SHRINE_PIECE:
            return "assets/red_shrine.png";
        case CarryableItemType::BLUE_SHRINE_PIECE:
            return "assets/blue_shrine.png";
        case CarryableItemType::YELLOW_SHRINE_PIECE:
            return "assets/yellow_shrine.png";
    }
}