#include "board.h"

bool Board::isNearIntersect(const sf::Rect<float>& rectangle1, sf::Rect<float> rectangle2) {
    // Rectangles with negative dimensions are allowed, so we must handle them correctly

    // Compute the min and max of the first rectangle on both axes
    float r1MinX = std::min(rectangle1.left, static_cast<float>(rectangle1.left + rectangle1.width));
    float r1MaxX = std::max(rectangle1.left, static_cast<float>(rectangle1.left + rectangle1.width));
    float r1MinY = std::min(rectangle1.top, static_cast<float>(rectangle1.top + rectangle1.height));
    float r1MaxY = std::max(rectangle1.top, static_cast<float>(rectangle1.top + rectangle1.height));

    // Compute the min and max of the second rectangle on both axes
    float r2MinX = std::min(rectangle2.left, static_cast<float>(rectangle2.left + rectangle2.width));
    float r2MaxX = std::max(rectangle2.left, static_cast<float>(rectangle2.left + rectangle2.width));
    float r2MinY = std::min(rectangle2.top, static_cast<float>(rectangle2.top + rectangle2.height));
    float r2MaxY = std::max(rectangle2.top, static_cast<float>(rectangle2.top + rectangle2.height));

    // Compute the intersection boundaries
    float interLeft = std::max(r1MinX, r2MinX);
    float interTop = std::max(r1MinY, r2MinY);
    float interRight = std::min(r1MaxX, r2MaxX) + 20;
    float interBottom = std::min(r1MaxY, r2MaxY) + 20;

    // If the intersection is valid (positive non zero area), then there is an intersection
    if ((interLeft < interRight) && (interTop < interBottom)) {
        return true;
    }

    return false;
}
