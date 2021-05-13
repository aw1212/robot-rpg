#include "item.h"

////////////////////////////
///CONSTRUCTOR/DESTRUCTOR///
////////////////////////////

Item::Item(const std::string& textureFile, bool visible) {
    this->visible = visible;
    initSprite(textureFile);
}

Item::~Item() {
}

///////////////
///ACCESSORS///
///////////////

sf::Sprite& Item::getItemSprite() {
    return itemSprite;
}

bool Item::isVisible() {
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

void Item::initSprite(const std::string& textureFile) {
    if (!itemTexture.loadFromFile(textureFile)) {
        //return EXIT_FAILURE;
    }

    itemSprite.setTexture(itemTexture);
    itemSprite.setPosition(180, 180);
}